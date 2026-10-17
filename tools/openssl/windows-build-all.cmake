# The standalone OpenSSL project owns building; this file owns ca2 storage/staging.
if(__REACTOS__)
    set(ca2_openssl_version 3.0.22)
    set(default_openssl_install "${PORT_STORAGE_ROOT}/${CMAKE_BUILD_TYPE}/binary")
else()
    set(ca2_openssl_version 3.5.8)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(openssl_arch x64)
    else()
        set(openssl_arch Win32)
    endif()
    set(default_openssl_install "${CMAKE_SOURCE_DIR}/../operating_system/storage-windows/${openssl_arch}/${CMAKE_BUILD_TYPE}/binary")
endif()
set(OPENSSL_VERSION "${ca2_openssl_version}" CACHE STRING "OpenSSL release required by windows-build-all")
set(OPENSSL_INSTALL_DIR "${default_openssl_install}" CACHE PATH "Installed OpenSSL SDK")
set(CA2_OPENSSL_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/port/external_build/openssl"
    CACHE PATH "Standalone OpenSSL CMake project")
add_subdirectory("${CA2_OPENSSL_SOURCE_DIRECTORY}" "${CMAKE_CURRENT_BINARY_DIR}/external-openssl")
# Application directories are added after port/. Prefer this SDK's generated
# headers to the legacy OpenSSL headers in the broad platform include trees.
get_property(openssl_parent_includes DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY INCLUDE_DIRECTORIES)
list(PREPEND openssl_parent_includes "${OPENSSL_INSTALL_DIR}/include")
list(REMOVE_DUPLICATES openssl_parent_includes)
set_property(DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY INCLUDE_DIRECTORIES "${openssl_parent_includes}")
add_custom_target(openssl_xp_build DEPENDS openssl_build)
add_custom_target(openssl_runtime
    COMMAND "${CMAKE_COMMAND}" "-DINSTALL_DIR=${OPENSSL_INSTALL_DIR}"
        "-DOUTPUT_DIR=${EXECUTABLE_OUTPUT_PATH}" "-DDEPLOY_DIR=${CA2_REACTOS_DEPLOY_DIRECTORY}"
        "-DXP=${__REACTOS__}" "-DOBJCOPY=${CMAKE_OBJCOPY}"
        -P "${CMAKE_CURRENT_LIST_DIR}/stage-runtime.cmake"
    DEPENDS openssl_build
    COMMENT "Staging OpenSSL runtime DLLs" VERBATIM)
# Imported-target dependencies are followed transitively by application consumers.
add_dependencies(libcrypto openssl_runtime)
add_dependencies(libssl openssl_runtime)
add_dependencies(openssl_xp_build openssl_runtime)
if(TARGET port_all)
    add_dependencies(port_all openssl_runtime)
endif()
