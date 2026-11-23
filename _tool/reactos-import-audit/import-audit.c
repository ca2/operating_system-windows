#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define LIMIT 2048
typedef struct Module {
 char path[MAX_PATH]; unsigned char *data; DWORD size; WORD machine, magic;
 IMAGE_SECTION_HEADER *sections; WORD count; DWORD headers;
 IMAGE_DATA_DIRECTORY exports, imports, delays; uint64_t base; int scanned;
} Module;
static Module *modules[LIMIT];
static int module_count, missing, errors, imports_checked;
static char root[MAX_PATH], system_dir[MAX_PATH], windows_dir[MAX_PATH];
static void scan(Module *m);
static void issue(const char *kind, const char *from, const char *dll, const char *symbol) {
 printf("%s | %s | %s | %s\n",kind,from,dll,symbol); missing++;
}
static void *rva(Module *m, DWORD address, size_t bytes) {
 DWORD offset=address; unsigned i;
 if(address >= m->headers) {
  int found=0;
  for(i=0;i<m->count;i++) {
   IMAGE_SECTION_HEADER *s=&m->sections[i];
   if(address>=s->VirtualAddress && (uint64_t)address-s->VirtualAddress < s->SizeOfRawData) {
    uint64_t pos=(uint64_t)s->PointerToRawData+address-s->VirtualAddress;
    if(pos>m->size) return NULL;
    offset=(DWORD)pos;found=1;break;
   }
  }
  if(!found) return NULL;
 }
 if((uint64_t)offset+bytes>m->size) return NULL;
 return m->data+offset;
}
static const char *string_rva(Module *m, DWORD address) {
 char *p=(char*)rva(m,address,1);
 return p && memchr(p,0,m->size-(size_t)(p-(char*)m->data)) ? p : NULL;
}
/* Debug sections normally trail the executable sections and can be enormous.
   Imports/exports do not require them. Retain a prefix covering headers and
   every non-debug section, without loading the DLL or changing its contents. */
/* COFF uses /<offset> for section names longer than eight characters.
   In particular MinGW stores .debug_info and friends this way. */
static int is_debug_section(FILE *f, const IMAGE_FILE_HEADER *fh,
                            const IMAGE_SECTION_HEADER *section, long length) {
 char name[9], prefix[6], *end; unsigned long offset; uint64_t position;
 long saved;
 if(!memcmp(section->Name,".debug",6)) return 1;
 if(section->Name[0]!='/' || !fh->PointerToSymbolTable) return 0;
 memcpy(name,section->Name,8);name[8]=0;
 offset=strtoul(name+1,&end,10);
 if(end==name+1 || *end || offset<4) return 0;
 position=(uint64_t)fh->PointerToSymbolTable+(uint64_t)fh->NumberOfSymbols*18+offset;
 if(position+sizeof(prefix)>(uint64_t)length) return 0;
 saved=ftell(f);if(saved<0) return 0;
 if(fseek(f,(long)position,SEEK_SET) || fread(prefix,1,sizeof(prefix),f)!=sizeof(prefix)) {
  fseek(f,saved,SEEK_SET);return 0;
 }
 if(fseek(f,saved,SEEK_SET)) return 0;
 return !memcmp(prefix,".debug",6);
}
static long audit_prefix_size(FILE *f, long length) {
 IMAGE_DOS_HEADER dos; IMAGE_FILE_HEADER fh; DWORD signature, headers;
 unsigned char optional[64]; IMAGE_SECTION_HEADER section;
 uint64_t section_pos, keep; unsigned i;
 rewind(f);
 if(fread(&dos,1,sizeof(dos),f)!=sizeof(dos) || dos.e_magic!=IMAGE_DOS_SIGNATURE || dos.e_lfanew<0) return length;
 if(fseek(f,dos.e_lfanew,SEEK_SET) || fread(&signature,1,4,f)!=4 || signature!=IMAGE_NT_SIGNATURE || fread(&fh,1,sizeof(fh),f)!=sizeof(fh)) return length;
 if(fh.SizeOfOptionalHeader<sizeof(optional) || fread(optional,1,sizeof(optional),f)!=sizeof(optional)) return length;
 memcpy(&headers,optional+60,sizeof(headers));
 section_pos=(uint64_t)dos.e_lfanew+4+sizeof(fh)+fh.SizeOfOptionalHeader;
 keep=section_pos+(uint64_t)fh.NumberOfSections*sizeof(section);
 if(keep>(uint64_t)length || headers>(DWORD)length) return length;
 if(headers>keep) keep=headers;
 if(fseek(f,(long)section_pos,SEEK_SET)) return length;
 for(i=0;i<fh.NumberOfSections;i++) {
  uint64_t end;
  if(fread(&section,1,sizeof(section),f)!=sizeof(section)) return length;
  end=(uint64_t)section.PointerToRawData+section.SizeOfRawData;
  if(end>(uint64_t)length) return length;
  if(!is_debug_section(f,&fh,&section,length) && end>keep) keep=end;
 }
 return (long)keep;
}
static Module *load(const char *path) {
 FILE *f; long length; Module *m; IMAGE_DOS_HEADER *dos; IMAGE_FILE_HEADER *fh;
 unsigned char *opt; DWORD nt; size_t end; int i;
 for(i=0;i<module_count;i++) if(!_stricmp(path,modules[i]->path)) return modules[i];
 f=fopen(path,"rb"); if(!f) return NULL;
 if(fseek(f,0,SEEK_END)|| (length=ftell(f))<0 || (unsigned long)length>0x7fffffffUL) {fclose(f);return NULL;}
 length=audit_prefix_size(f,length);
 rewind(f);m=(Module*)calloc(1,sizeof(*m)); if(!m){fclose(f);return NULL;}
 m->size=(DWORD)length; m->data=(unsigned char*)malloc(m->size?m->size:1);
 if(!m->data||fread(m->data,1,m->size,f)!=m->size){fclose(f);goto invalid;}
 fclose(f);strncpy(m->path,path,MAX_PATH-1);
 if(m->size<sizeof(IMAGE_DOS_HEADER)) goto invalid;
 dos=(IMAGE_DOS_HEADER*)m->data;
 if(dos->e_magic!=IMAGE_DOS_SIGNATURE||dos->e_lfanew<0) goto invalid;
 nt=(DWORD)dos->e_lfanew;
 if((uint64_t)nt+4+sizeof(*fh)>m->size||*(DWORD*)(m->data+nt)!=IMAGE_NT_SIGNATURE) goto invalid;
 fh=(IMAGE_FILE_HEADER*)(m->data+nt+4);opt=(unsigned char*)(fh+1);
 end=(size_t)(opt-m->data)+fh->SizeOfOptionalHeader;
 if(end>m->size||fh->SizeOfOptionalHeader<2) goto invalid;
 m->magic=*(WORD*)opt;m->machine=fh->Machine;m->count=fh->NumberOfSections;
 if(m->magic==IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
  IMAGE_OPTIONAL_HEADER32 *o=(IMAGE_OPTIONAL_HEADER32*)opt;
  if(fh->SizeOfOptionalHeader<sizeof(*o))goto invalid;
  m->headers=o->SizeOfHeaders;m->base=o->ImageBase;
  if(o->NumberOfRvaAndSizes>13){m->exports=o->DataDirectory[0];m->imports=o->DataDirectory[1];m->delays=o->DataDirectory[13];}
 } else if(m->magic==IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
  IMAGE_OPTIONAL_HEADER64 *o=(IMAGE_OPTIONAL_HEADER64*)opt;
  if(fh->SizeOfOptionalHeader<sizeof(*o))goto invalid;
  m->headers=o->SizeOfHeaders;m->base=o->ImageBase;
  if(o->NumberOfRvaAndSizes>13){m->exports=o->DataDirectory[0];m->imports=o->DataDirectory[1];m->delays=o->DataDirectory[13];}
 } else goto invalid;
 if(end+(size_t)m->count*sizeof(IMAGE_SECTION_HEADER)>m->size||module_count==LIMIT)goto invalid;
 m->sections=(IMAGE_SECTION_HEADER*)(m->data+end);
 modules[module_count++]=m;return m;
invalid:
 fprintf(stderr,"AUDIT ERROR: invalid/unreadable PE or module limit: %s\n",path);errors++;
 free(m->data);free(m);return NULL;
}
static Module *resolve(const char *name) {
 const char *dirs[3]={root,system_dir,windows_dir}; char path[MAX_PATH]; int i;
 /* Read files only. Never execute DLL initializers. */
 if(strchr(name,'/')||strchr(name,'\\')||strchr(name,':'))return NULL;
 for(i=0;i<3;i++) {
  if(strlen(dirs[i])+strlen(name)+2>=MAX_PATH)continue;
  strcpy(path,dirs[i]);strcat(path,"\\");strcat(path,name);
  if(GetFileAttributesA(path)!=INVALID_FILE_ATTRIBUTES) return load(path);
 }
 return NULL;
}
static int exported(Module *m,const char *name,DWORD ordinal,int by_ordinal,int depth) {
 IMAGE_EXPORT_DIRECTORY *e; DWORD index=0,*functions,*names; WORD *ordinals; unsigned i;
 if(depth>32||!m->exports.VirtualAddress)return 0;
 e=(IMAGE_EXPORT_DIRECTORY*)rva(m,m->exports.VirtualAddress,sizeof(*e));if(!e)return 0;
 if(e->NumberOfFunctions>m->size/4 || e->NumberOfNames>m->size/4)return 0;
 functions=(DWORD*)rva(m,e->AddressOfFunctions,(size_t)e->NumberOfFunctions*4);
 if(!functions)return 0;
 if(by_ordinal) {if(ordinal<e->Base||ordinal-e->Base>=e->NumberOfFunctions)return 0;index=ordinal-e->Base;}
 else {
  names=(DWORD*)rva(m,e->AddressOfNames,(size_t)e->NumberOfNames*4);
  ordinals=(WORD*)rva(m,e->AddressOfNameOrdinals,(size_t)e->NumberOfNames*2);
  if(!names||!ordinals)return 0;
  for(i=0;i<e->NumberOfNames;i++){const char *n=string_rva(m,names[i]);if(n&&!strcmp(n,name))break;}
  if(i==e->NumberOfNames)return 0;
  index=ordinals[i];
  if(index>=e->NumberOfFunctions)return 0;
 }
 if(!functions[index])return 0;
 if(functions[index]>=m->exports.VirtualAddress &&
    (uint64_t)functions[index]< (uint64_t)m->exports.VirtualAddress+m->exports.Size) {
  const char *f=string_rva(m,functions[index]);char forward[256],dll[256];char *dot;Module *target;
  if(!f||strlen(f)>=sizeof(forward))return 0;
  strcpy(forward,f);dot=strrchr(forward,'.');if(!dot)return 0;*dot++=0;
  snprintf(dll,sizeof(dll),"%s%s",forward,strchr(forward,'.')?"":".dll");
  target=resolve(dll);if(!target){printf("FORWARD TARGET: %s -> %s\n",m->path,dll);return 0;}
  if(target->machine!=m->machine)return 0;
  scan(target);
  return exported(target,dot,(DWORD)strtoul(dot+(*dot=='#'),NULL,10),*dot=='#',depth+1);
 }
 /* Data exports can reside in zero-filled (.bss) virtual section storage. */
 if(functions[index]<m->headers)return 1;
 for(i=0;i<m->count;i++) {
  IMAGE_SECTION_HEADER *section=&m->sections[i];
  DWORD extent=section->Misc.VirtualSize>section->SizeOfRawData?
      section->Misc.VirtualSize:section->SizeOfRawData;
  if(functions[index]>=section->VirtualAddress &&
     (uint64_t)functions[index]-section->VirtualAddress<extent)return 1;
 }
 return 0;
}
static void thunks(Module *from,const char *dll,DWORD lookup,const char *kind) {
 Module *target=resolve(dll);unsigned index;unsigned width=from->magic==IMAGE_NT_OPTIONAL_HDR64_MAGIC?8:4;
 if(!target){issue("MISSING DLL",from->path,dll,kind);return;}
 if(target->machine!=from->machine){issue("WRONG ARCH",from->path,target->path,kind);return;}
 for(index=0;index<from->size/width;index++) {
  void *p;uint64_t value,flag=width==8?UINT64_C(0x8000000000000000):0x80000000UL;
  const char *name=NULL;char label[32];DWORD ordinal=0;
  if((uint64_t)lookup+index*width>UINT32_MAX)break;
  p=rva(from,lookup+index*width,width);if(!p){errors++;break;}
  value=width==8?*(uint64_t*)p:*(DWORD*)p;if(!value)break;
  if(value&flag){ordinal=(DWORD)(value&0xffff);snprintf(label,sizeof(label),"#%lu",(unsigned long)ordinal);name=label;}
  else if(value<=UINT32_MAX-2)name=string_rva(from,(DWORD)value+2);
  if(!name){errors++;break;}
  imports_checked++;
  if(!exported(target,name,ordinal,(value&flag)!=0,0))issue(kind,from->path,target->path,name);
 }
 scan(target);
}
typedef struct Delay {DWORD attributes,name,handle,iat,intable,bound,unload,timestamp;} Delay;
static DWORD delay_rva(Module *m,DWORD value,DWORD attributes) {
 if(attributes&1)return value;
 return value>=m->base?(DWORD)(value-m->base):0;
}
static void scan(Module *m) {
 unsigned i;if(m->scanned)return;m->scanned=1;
 printf("MODULE | %s\n",m->path);
 for(i=0;m->imports.VirtualAddress&&i<m->imports.Size/sizeof(IMAGE_IMPORT_DESCRIPTOR);i++) {
  IMAGE_IMPORT_DESCRIPTOR *d=(IMAGE_IMPORT_DESCRIPTOR*)rva(m,m->imports.VirtualAddress+i*sizeof(*d),sizeof(*d));const char *name;
  if(!d){errors++;break;}if(!d->Name)break;name=string_rva(m,d->Name);if(!name){errors++;break;}
  thunks(m,name,d->OriginalFirstThunk?d->OriginalFirstThunk:d->FirstThunk,"MISSING SYMBOL");
 }
 for(i=0;m->delays.VirtualAddress&&i<m->delays.Size/sizeof(Delay);i++) {
  Delay *d=(Delay*)rva(m,m->delays.VirtualAddress+i*sizeof(*d),sizeof(*d));const char *name;DWORD lookup;
  if(!d){errors++;break;}if(!d->name)break;name=string_rva(m,delay_rva(m,d->name,d->attributes));
  lookup=delay_rva(m,d->intable,d->attributes);if(!name||!lookup){errors++;break;}
  thunks(m,name,lookup,"MISSING DELAY SYMBOL");
 }
}
int main(int argc,char **argv) {
 char full[MAX_PATH];Module *start;int i,all=0;const char *exe="_app_app.exe";
 if(argc>1&&!strcmp(argv[1],"--help")){puts("import-audit.exe [executable] [--all]\nReads imports recursively. --all also scans every local DLL. Reports to stdout.\nExit: 0 no missing imports, 1 missing imports, 2 audit errors.\nSearch: executable directory, System32, Windows. No PATH/SxS/API-set emulation.");return 0;}
 for(i=1;i<argc;i++) {if(!strcmp(argv[i],"--all"))all=1;else exe=argv[i];}
 if(!GetFullPathNameA(exe,sizeof(full),full,NULL)||strlen(full)>=MAX_PATH-1)return 2;
 strcpy(root,full);{char *slash=strrchr(root,'\\');if(!slash)return 2;*slash=0;}
 GetSystemDirectoryA(system_dir,sizeof(system_dir));GetWindowsDirectoryA(windows_dir,sizeof(windows_dir));
 puts("ReactOS import audit (static imports; DLLs are read, never loaded)");
 printf("ROOT | %s\nSYSTEM | %s\n",root,system_dir);
 start=load(full);if(!start){fprintf(stderr,"Cannot read executable: %s\n",full);return 2;}scan(start);
 if(all){WIN32_FIND_DATAA entry;HANDLE h;char pattern[MAX_PATH];snprintf(pattern,sizeof(pattern),"%s\\*.dll",root);h=FindFirstFileA(pattern,&entry);
  if(h!=INVALID_HANDLE_VALUE){do{Module *m;if(!(entry.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)){m=resolve(entry.cFileName);if(m)scan(m);}}while(FindNextFileA(h,&entry));FindClose(h);}}
 printf("\nSUMMARY | modules=%d imports=%d missing=%d audit_errors=%d\n",module_count,imports_checked,missing,errors);
 for(i=0;i<module_count;i++){free(modules[i]->data);free(modules[i]);}
 return errors?2:missing?1:0;
}
