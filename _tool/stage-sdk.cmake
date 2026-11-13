# Keep the SDK prefix independent from the shared runtime/import-library layout.
if(NOT INSTALL_DIR OR NOT STORAGE_BINARY_DIR)
    message(FATAL_ERROR "INSTALL_DIR and STORAGE_BINARY_DIR are required")
endif()
get_filename_component(storage_configuration "${STORAGE_BINARY_DIR}" DIRECTORY)
set(storage_library "${storage_configuration}/library")
file(MAKE_DIRECTORY "${STORAGE_BINARY_DIR}" "${storage_library}")
file(GLOB sdk_binaries "${INSTALL_DIR}/bin/*.dll" "${INSTALL_DIR}/bin/*.exe")
file(GLOB sdk_libraries "${INSTALL_DIR}/lib/*.lib" "${INSTALL_DIR}/lib/*.a")
foreach(binary IN LISTS sdk_binaries)
    execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "${binary}" "${STORAGE_BINARY_DIR}" COMMAND_ERROR_IS_FATAL ANY)
endforeach()
foreach(library IN LISTS sdk_libraries)
    execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "${library}" "${storage_library}" COMMAND_ERROR_IS_FATAL ANY)
endforeach()
if(EXISTS "${INSTALL_DIR}/lib/ossl-modules")
    file(COPY "${INSTALL_DIR}/lib/ossl-modules/"
        DESTINATION "${STORAGE_BINARY_DIR}/ossl-modules")
endif()
