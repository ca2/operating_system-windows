# windows-build-all owns dependency policy; the external project stays standalone.
# -DFFMPEG_* overrides remain available in CLion/CMake profiles.
if(__REACTOS__)
    set(default_ffmpeg_install "${PORT_STORAGE_ROOT}/${CMAKE_BUILD_TYPE}/third/ffmpeg-xp")
else()
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ca2_ffmpeg_arch x64)
    else()
        set(ca2_ffmpeg_arch Win32)
    endif()
    set(default_ffmpeg_install "${CMAKE_SOURCE_DIR}/../operating_system/storage-windows/${ca2_ffmpeg_arch}/${CMAKE_BUILD_TYPE}/third/ffmpeg")
endif()
if(__REACTOS__)
    set(ca2_ffmpeg_version 6.1.6)
else()
    set(ca2_ffmpeg_version 9.0.2)
endif()
set(FFMPEG_VERSION "${ca2_ffmpeg_version}" CACHE STRING "FFmpeg release required by windows-build-all")
set(FFMPEG_INSTALL_DIR "${default_ffmpeg_install}" CACHE PATH "Installed FFmpeg SDK")
option(FFMPEG_BUILD_PROGRAMS "Build optional FFmpeg CLI tools" OFF)
option(FFMPEG_NETWORK "Enable FFmpeg network protocols" OFF)
set(FFMPEG_EXTRA_CONFIGURE_ARGS "" CACHE STRING "FFmpeg codec/format configuration as a CMake list")
set(CA2_FFMPEG_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/port/external_build/ffmpeg"
    CACHE PATH "Standalone FFmpeg CMake project")
# CMAKE_BUILD_TYPE and the compiler/toolchain are inherited from the parent.
add_subdirectory("${CA2_FFMPEG_SOURCE_DIRECTORY}" "${CMAKE_CURRENT_BINARY_DIR}/external-ffmpeg")
add_custom_target(ffmpeg_xp_build DEPENDS ffmpeg_build) # Existing CLion configuration.
foreach(component IN ITEMS avutil swresample avformat avcodec swscale)
    get_target_property(ffmpeg_dll ${component} IMPORTED_LOCATION)
    get_filename_component(ffmpeg_dll_name "${ffmpeg_dll}" NAME)
    set(output "${EXECUTABLE_OUTPUT_PATH}/${ffmpeg_dll_name}")
    add_custom_command(OUTPUT "${output}"
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${EXECUTABLE_OUTPUT_PATH}"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${ffmpeg_dll}" "${output}"
        DEPENDS ffmpeg_build "${ffmpeg_dll}" VERBATIM)
    add_custom_target(port_runtime_${component} DEPENDS "${output}")
    if(__REACTOS__ AND CA2_REACTOS_DEPLOY_DIRECTORY)
        add_custom_command(TARGET port_runtime_${component} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" "-DSOURCE_FILE=${ffmpeg_dll}"
                "-DDESTINATION=${CA2_REACTOS_DEPLOY_DIRECTORY}" "-DOBJCOPY=${CMAKE_OBJCOPY}"
                -P "${CMAKE_SOURCE_DIR}/operating_system/operating_system-windows/tools/reactos-import-audit/deployment-copy.cmake" VERBATIM)
    endif()
    add_dependencies(port_all port_runtime_${component})
endforeach()
add_dependencies(port_all ffmpeg_build)

# 32-bit FFmpeg may use GCC's out-of-line 64-bit atomics. Other compiler
# runtimes are already staged by ca2; keep this additional runtime explicit.
if(MINGW)
    get_filename_component(ffmpeg_compiler_directory "${CMAKE_C_COMPILER}" DIRECTORY)
    set(ffmpeg_atomic_runtime "${ffmpeg_compiler_directory}/libatomic-1.dll")
    if(EXISTS "${ffmpeg_atomic_runtime}")
        add_custom_target(port_runtime_ffmpeg_atomic
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "${ffmpeg_atomic_runtime}" "${EXECUTABLE_OUTPUT_PATH}/libatomic-1.dll"
            VERBATIM)
        if(__REACTOS__ AND CA2_REACTOS_DEPLOY_DIRECTORY)
            add_custom_command(TARGET port_runtime_ffmpeg_atomic POST_BUILD
                COMMAND "${CMAKE_COMMAND}" "-DSOURCE_FILE=${ffmpeg_atomic_runtime}"
                    "-DDESTINATION=${CA2_REACTOS_DEPLOY_DIRECTORY}" "-DOBJCOPY=${CMAKE_OBJCOPY}"
                    -P "${CMAKE_SOURCE_DIR}/operating_system/operating_system-windows/tools/reactos-import-audit/deployment-copy.cmake" VERBATIM)
        endif()
        add_dependencies(port_all port_runtime_ffmpeg_atomic)
    endif()
endif()
