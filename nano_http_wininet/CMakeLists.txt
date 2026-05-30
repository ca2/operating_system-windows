cmake_minimum_required(VERSION 3.17)
project(nano_http_wininet CXX)





message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")



if(${WIN32})
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


list(APPEND library_source
        _.cpp
        _.h
        _factory.cpp
        #_curl.cpp
        #_wget.cpp
   connect.cpp
   connect.h
   #_nano_http.cpp
   #_nano_http.h
   #curl_easy.cpp
   #curl_easy.h
   hinternet.cpp
   hinternet.h
   http.cpp
   http.h
request.cpp
request.h)


add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

#set_target_properties${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)



if(${WIN32})
   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/static_${PROJECT_NAME}}.lib")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/static_${PROJECT_NAME}}.def")
   target_link_libraries(${PROJECT_NAME} PRIVATE acme apex aqua aura Gdiplus)
elseif (${LINUX})

   message("PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})

endif ()



#target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE)
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE)
