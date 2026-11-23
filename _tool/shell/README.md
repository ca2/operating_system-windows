# Portable checkout shell

Run ./build.ps1 to build the CRT-free x86 shell.exe and deploy it to ../../tool/bin.
--initialize-project-root copies this executable to checkout tool/bin/shell.exe
for committing. --initialize-project-root-instance creates the ignored root
shell.lnk with the copied tool/image/shell.ico blue icon. The first root
./tool/shell run invokes this instance setup automatically.

shell.cpp includes ../architecure_launcher/launcher.h and embeds the relative
folder operating_system/operating_system-windows/tool/bin and executable
launch_shell.exe. Extra arguments are forwarded, not interpreted as routing
settings. The launcher resolves the checkout beside itself and selects x86,
x64, or arm64, independently of Explorer's current directory. The executable contains no machine-specific path; its routing survives a move.
The root .lnk uses a relative target-resolution hint, but absolute icon and
working-directory properties for Windows compatibility. Reinitialize after a move.

Generate native launch_shell.exe using application_build_helper
--create-shortcut-executables, then deploy it with its matching helper into
tool/bin/<architecture>. The root launcher alone does not provide XP/ReactOS
compatibility for those executables or Git for Windows.
