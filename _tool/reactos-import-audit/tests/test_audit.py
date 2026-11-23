import struct
import subprocess
import tempfile
from pathlib import Path

def image(directory, filename, imports=None, export=None):
    data = bytearray(2048)
    struct.pack_into('<H', data, 0, 0x5a4d)
    struct.pack_into('<I', data, 60, 128)
    data[128:132] = b'PE\0\0'
    struct.pack_into('<HHIIIHH', data, 132, 0x14c, 1, 0, 0, 0, 224, 0x102)
    optional = 152
    struct.pack_into('<H', data, optional, 0x10b)
    struct.pack_into('<I', data, optional+28, 0x400000)
    struct.pack_into('<I', data, optional+60, 512)
    struct.pack_into('<I', data, optional+92, 16)
    section = optional+224
    data[section:section+8] = b'.data\0\0\0'
    struct.pack_into('<IIII', data, section+8, 1536, 0x1000, 1536, 512)
    def at(rva): return rva-0x1000+512
    def text(rva, value):
        encoded = value.encode()+b'\0'
        data[at(rva):at(rva)+len(encoded)] = encoded
    if imports:
        dll, entries = imports
        struct.pack_into('<II', data, optional+104, 0x1000, 40)
        struct.pack_into('<IIIII', data, at(0x1000), 0x1080, 0, 0, 0x1060, 0x1080)
        text(0x1060, dll)
        next_name = 0x1200
        for index, entry in enumerate(entries):
            if isinstance(entry, int): value = 0x80000000 | entry
            else:
                value = next_name
                text(next_name+2, entry)
                next_name += 64
            struct.pack_into('<I', data, at(0x1080)+index*4, value)
    if export:
        entries = export
        struct.pack_into('<II', data, optional+96, 0x1000, 0x200)
        struct.pack_into('<IIHHIIIIIII', data, at(0x1000), 0, 0, 0, 0, 0, 7, len(entries), len(entries), 0x1040, 0x1060, 0x1080)
        for index, (name, forward) in enumerate(entries):
            target = 0x1100+index*64 if forward else 0x1400
            struct.pack_into('<I', data, at(0x1040)+index*4, target)
            struct.pack_into('<I', data, at(0x1060)+index*4, 0x1200+index*64)
            struct.pack_into('<H', data, at(0x1080)+index*2, index)
            text(0x1200+index*64, name)
            if forward: text(target, forward)
    (directory/filename).write_bytes(data)

exe = Path(__file__).resolve().parents[1]/'import-audit.exe'
with tempfile.TemporaryDirectory() as tmp:
    directory = Path(tmp)
    image(directory, 'demo.dll', export=[('Good', None), ('Forward', 'next.Pass')])
    image(directory, 'next.dll', export=[('Pass', None)])
    image(directory, 'ok.exe', imports=('demo.dll', ['Good', 'Forward', 7]))
    result = subprocess.run([str(exe), str(directory/'ok.exe')], capture_output=True, text=True)
    assert result.returncode == 0, result.stdout+result.stderr
    # Named/ordinal data exports in the zero-filled virtual tail are valid.
    bss = bytearray((directory/'demo.dll').read_bytes())
    struct.pack_into('<I', bss, 152+224+16, 1024)
    (directory/'demo.dll').write_bytes(bss)
    result = subprocess.run([str(exe), str(directory/'ok.exe')], capture_output=True, text=True)
    assert result.returncode == 0, result.stdout+result.stderr
    # Debug data may trail the useful PE sections; it is not needed for imports.
    debug = bytearray((directory/'demo.dll').read_bytes())
    struct.pack_into('<H', debug, 134, 2)
    section = 152 + 224 + 40
    debug[section:section+8] = b'.debug\0\0'
    struct.pack_into('<IIII', debug, section+8, 65536, 0x3000, 65536, 2048)
    debug.extend(bytes(65536))
    (directory/'demo.dll').write_bytes(debug)
    result = subprocess.run([str(exe), str(directory/'ok.exe')], capture_output=True, text=True)
    assert result.returncode == 0, result.stdout+result.stderr
    # Real MinGW debug section names use COFF string-table references.
    debug[section:section+8] = b'/4\0\0\0\0\0\0'
    string_table = len(debug)
    struct.pack_into('<I', debug, 140, string_table)
    debug.extend(struct.pack('<I', 16) + b'.debug_info\0')
    (directory/'demo.dll').write_bytes(debug)
    result = subprocess.run([str(exe), str(directory/'ok.exe')], capture_output=True, text=True)
    assert result.returncode == 0, result.stdout+result.stderr
    image(directory, 'bad.exe', imports=('demo.dll', ['Absent', 9]))
    result = subprocess.run([str(exe), str(directory/'bad.exe')], capture_output=True, text=True)
    assert result.returncode == 1 and '| Absent' in result.stdout and '| #9' in result.stdout, result.stdout
    image(directory, 'missing.exe', imports=('absent-fixture.dll', ['Good']))
    result = subprocess.run([str(exe), str(directory/'missing.exe')], capture_output=True, text=True)
    assert result.returncode == 1 and 'MISSING DLL' in result.stdout, result.stdout
    image(directory, 'delay.exe', imports=('demo.dll', ['Absent']))
    delayed = bytearray((directory/'delay.exe').read_bytes())
    struct.pack_into('<II', delayed, 152+104, 0, 0)
    struct.pack_into('<II', delayed, 152+96+13*8, 0x1000, 64)
    struct.pack_into('<IIIIIIII', delayed, 512, 1, 0x1060, 0, 0x1080, 0x1080, 0, 0, 0)
    (directory/'delay.exe').write_bytes(delayed)
    result = subprocess.run([str(exe), str(directory/'delay.exe')], capture_output=True, text=True)
    assert result.returncode == 1 and 'MISSING DELAY SYMBOL' in result.stdout, result.stdout
    (directory/'invalid.exe').write_bytes(b'not a PE file')
    result = subprocess.run([str(exe), str(directory/'invalid.exe')], capture_output=True, text=True)
    assert result.returncode == 2, result.stdout
print('PASS: named exports, ordinals, forwarders, missing DLLs/symbols, delay imports, malformed PE')
