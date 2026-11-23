include_guard(GLOBAL)

# Enable the OS-provided themed common controls (available since Windows XP).
# No supportedOS, DPI, execution-level, or minimum-Windows policy is changed.
function(ca2_enable_windows_common_controls target)
    if(NOT WIN32)
        return()
    endif()
    if(NOT TARGET "${target}")
        message(FATAL_ERROR "Common controls: unknown target '${target}'")
    endif()
    get_target_property(type "${target}" TYPE)
    if(NOT type STREQUAL "EXECUTABLE")
        message(FATAL_ERROR "Common controls require an executable target: ${target}")
    endif()
    get_target_property(enabled "${target}" CA2_WINDOWS_COMMON_CONTROLS)
    if(enabled)
        return()
    endif()
    set_property(TARGET "${target}" PROPERTY CA2_WINDOWS_COMMON_CONTROLS TRUE)

    if(MSVC)
        # Let the linker merge this dependency into its existing application
        # manifest, retaining any other manifest settings provided by the target.
        target_link_options("${target}" PRIVATE
            "/MANIFESTDEPENDENCY:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'")
    else()
        # Some MinGW GCC distributions inject a second, non-neutral manifest
        # from default-manifest.o. Override only that endfile entry for targets
        # supplying their own manifest; never modify the installed toolchain.
        if(MINGW AND CMAKE_C_COMPILER_ID STREQUAL "GNU" OR
            MINGW AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            if(CMAKE_CXX_COMPILER_LOADED)
                set(compiler "${CMAKE_CXX_COMPILER}")
            else()
                set(compiler "${CMAKE_C_COMPILER}")
            endif()
            get_property(checked GLOBAL PROPERTY CA2_COMMON_CONTROLS_GCC_CHECKED)
            if(NOT checked)
                execute_process(COMMAND "${compiler}" -dumpspecs
                    OUTPUT_VARIABLE specs RESULT_VARIABLE result)
                if(NOT result EQUAL 0)
                    message(FATAL_ERROR "Could not inspect GCC manifest defaults")
                endif()
                if(specs MATCHES "\\*endfile:\n([^\n]+)")
                    set(endfile "${CMAKE_MATCH_1}")
                    string(REPLACE "%{!shared:%:if-exists(default-manifest.o%s)}" ""
                        replacement "${endfile}")
                    if(NOT replacement STREQUAL endfile)
                        set(specs_path "${CMAKE_BINARY_DIR}/common-controls.specs")
                        file(CONFIGURE OUTPUT "${specs_path}"
                            CONTENT "*endfile:\n@replacement@\n\n" @ONLY)
                        set_property(GLOBAL PROPERTY CA2_COMMON_CONTROLS_GCC_SPECS "${specs_path}")
                    endif()
                endif()
                set_property(GLOBAL PROPERTY CA2_COMMON_CONTROLS_GCC_CHECKED TRUE)
            endif()
            get_property(specs_path GLOBAL PROPERTY CA2_COMMON_CONTROLS_GCC_SPECS)
            if(specs_path)
                target_link_options("${target}" PRIVATE "-specs=${specs_path}")
                set_property(TARGET "${target}" APPEND PROPERTY LINK_DEPENDS "${specs_path}")
            endif()
        endif()
        if(NOT CMAKE_RC_COMPILER_LOADED)
            enable_language(RC)
        endif()
        set(directory "${CMAKE_CURRENT_BINARY_DIR}/common-controls/${target}")
        file(MAKE_DIRECTORY "${directory}")
        set(manifest "${directory}/common-controls.manifest")
        configure_file("${CMAKE_CURRENT_FUNCTION_LIST_DIR}/common-controls.manifest"
            "${manifest}" COPYONLY)
        # Resource 1 is CREATEPROCESS_MANIFEST_RESOURCE_ID; numeric resource
        # type 24 is RT_MANIFEST, accepted by both windres and Windows rc.exe.
        file(CONFIGURE OUTPUT "${directory}/common-controls.rc"
            CONTENT "1 24 \"@manifest@\"\n" @ONLY)
        set_property(SOURCE "${directory}/common-controls.rc" APPEND
            PROPERTY OBJECT_DEPENDS "${manifest}")
        target_sources("${target}" PRIVATE "${directory}/common-controls.rc")
    endif()
endfunction()
