call "%VS_VARS%"  %VS_VARS_PLAT2%

cl /Yu"framework.h" /MP /GS /Qpar- /W3 /Gy- /Zc:wchar_t /I"%CA2_ROOT%include" /I"%CA2_ROOT%app/include" /I"." /I"%CA2_ROOT%app-core/netnode_dynamic_source_library/framework" /I"%CA2_ROOT%" /I"%CA2_ROOT%app" /I"%CA2_ROOT%app/base/include" /I"%CA2_ROOT%app/base" /I"%CA2_ROOT%app" /I"%CA2_ROOT%app/aura" /I"%CA2_ROOT%app/base" /I"%CA2_ROOT%app/axis" /I"%CA2_ROOT%app/aura" /I"%CA2_ROOT%app/axis" /I"%CA2_ROOT%platform/thirdparty" /I"%CA2_ROOT%platform/seed/metaseed/../../" /I"%CA2_ROOT%app-core/netnode_dynamic_source_library/../.." /I"%CA2_ROOT%app-core/netnode_dynamic_source_library/../../" /I"%CA2_ROOT%app-core/netnode_dynamic_source_library/../" /I"%CA2_ROOT%app-core/netnode_dynamic_source_library"  /I"%NETNODE_ROOT%net/netseed" /I"%NETNODE_ROOT%net/netseed/include" /I"%CA2_ROOT%time/dynamic_source/library/include"  /Zi /Gm- /Od /Ob0 /sdl /Fd"%CA2_ROOT%time/intermediate/x64/%CONFIGURATION%/netnode_dynamic_source_library/%SDK1%.pdb" /Zc:inline /fp:fast /D "MEMDLEAK" /D "_NETNODE_LIBRARY_LIBRARY" /D "_WINDLL" /D "_MBCS" /fp:except- /errorReport:prompt /GF- /WX- /Zc:forScope /RTC1 /GR /Gd /MDd /openmp- /FC /Fa"%CA2_ROOT%time/intermediate/x64/%CONFIGURATION%/netnode_dynamic_source_library/" /EHa /nologo /Fo"%CA2_ROOT%time/intermediate/x64/%CONFIGURATION%/netnode_dynamic_source_library/" /Fp"%CA2_ROOT%time/intermediate/x64/%CONFIGURATION%/netnode_dynamic_source_library/netnode_dynamic_source_library.pch"  /Zm384 /bigobj /c "%CA2_ROOT%time/dynamic_source/%ITEM_NAME%.cpp" > "%CA2_ROOT%time/dynamic_source/%ITEM_NAME%-compile-log.txt" 