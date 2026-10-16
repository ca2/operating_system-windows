cmake_minimum_required(VERSION 3.17)
project(audio_mixer_mmsystem CXX)

set(library_source
    _.cpp _factory.cpp platform.cpp audio_mixer.cpp control.cpp department.cpp
    destination.cpp device.cpp interaction.cpp line_info.cpp source.cpp thread.cpp)
add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})
foreach(mixer_target IN ITEMS ${PROJECT_NAME} static_${PROJECT_NAME})
    target_compile_definitions(${mixer_target} PRIVATE _${PROJECT_NAME}_project)
    target_include_directories(${mixer_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
    target_link_libraries(${mixer_target} PRIVATE
        acme apex aqua aura acme_windows audio_mixer multimedia_mmsystem winmm)
    if(NOT NO_PRECOMPILED_HEADER)
        target_precompile_headers(${mixer_target} PRIVATE platform.h)
    endif()
endforeach()
if(MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
else()
    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
    target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
endif()