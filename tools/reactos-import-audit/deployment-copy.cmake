# Copy only runtime PE files. Original debug files are never modified.
if(NOT DESTINATION OR NOT OBJCOPY)
    message(FATAL_ERROR "Deployment requires DESTINATION and OBJCOPY")
endif()
get_filename_component(DESTINATION "${DESTINATION}" ABSOLUTE)
file(MAKE_DIRECTORY "${DESTINATION}")
if(SOURCE_FILE)
    set(files "${SOURCE_FILE}")
elseif(RUNTIME_ONLY)
    file(GLOB files "${SOURCE_DIRECTORY}/libgcc_s_*.dll" "${SOURCE_DIRECTORY}/libstdc++-6.dll"
        "${SOURCE_DIRECTORY}/libwinpthread-1.dll" "${SOURCE_DIRECTORY}/libcrypto*.dll" "${SOURCE_DIRECTORY}/libssl*.dll")
    # Some upstream port CMake files do not call project(), so their runtime
    # copies also need staging when the application is linked.
    foreach(name IN ITEMS archive iconv idn zlib unac sqlite pcre png freetype pixman cairo
        port_jpeg port_webp port_jxr port_openexr port_openjpeg port_tiff4 port_rawlite port_freeimage)
        if(EXISTS "${SOURCE_DIRECTORY}/${name}.dll")
            list(APPEND files "${SOURCE_DIRECTORY}/${name}.dll")
        endif()
    endforeach()
else()
    file(GLOB files "${SOURCE_DIRECTORY}/*.exe" "${SOURCE_DIRECTORY}/*.dll")
endif()
foreach(source IN LISTS files)
    get_filename_component(name "${source}" NAME)
    get_filename_component(source "${source}" ABSOLUTE)
    set(output "${DESTINATION}/${name}")
    string(TOLOWER "${source}" source_comparison)
    string(TOLOWER "${output}" output_comparison)
    if(source_comparison STREQUAL output_comparison)
        message(FATAL_ERROR "ReactOS deployment must use a separate directory")
    endif()
    if(EXISTS "${output}" AND "${output}" IS_NEWER_THAN "${source}" AND
       "${output}" IS_NEWER_THAN "${CMAKE_CURRENT_LIST_FILE}")
        continue()
    endif()
    # Multiple application targets may stage the same runtime concurrently.
    # Publish only a complete file; a failed strip must not look up to date.
    string(RANDOM LENGTH 12 ALPHABET 0123456789abcdef temporary_id)
    set(temporary "${output}.${temporary_id}.tmp")
    execute_process(COMMAND "${OBJCOPY}" --strip-debug --preserve-dates "${source}" "${temporary}"
        RESULT_VARIABLE result ERROR_VARIABLE error)
    if(NOT result EQUAL 0)
        file(REMOVE "${temporary}")
        message(FATAL_ERROR "ReactOS deployment failed for ${name}: ${error}")
    endif()
    # A loaded DLL may be readable but cannot be replaced on Windows. Avoid
    # replacing identical stripped bytes after script/configuration changes.
    if(EXISTS "${output}")
        file(SHA256 "${temporary}" temporary_hash)
        file(SHA256 "${output}" output_hash)
        if(temporary_hash STREQUAL output_hash)
            file(REMOVE "${temporary}")
            continue()
        endif()
    endif()
    file(RENAME "${temporary}" "${output}")
endforeach()
if(SOURCE_DIRECTORY)
    foreach(name IN ITEMS import-audit.exe audit-imports.cmd dll-load-probe.exe probe-windowing.cmd run-app-with-exit-code.cmd capture-console.cmd)
        execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/${name}" "${DESTINATION}/${name}"
            COMMAND_ERROR_IS_FATAL ANY)
    endforeach()
endif()
