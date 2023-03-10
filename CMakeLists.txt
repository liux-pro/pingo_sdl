cmake_minimum_required(VERSION 3.7)

project(pingo_sdl)
set(CMAKE_C_STANDARD 99)


include_directories(.)
aux_source_directory(${CMAKE_SOURCE_DIR} SRC)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sUSE_SDL=2 --shell-file ${CMAKE_SOURCE_DIR}/shell_minimal.html")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -sUSE_SDL=2 --shell-file ${CMAKE_SOURCE_DIR}/shell_minimal.html")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
else ()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif ()

add_executable("${PROJECT_NAME}" ${SRC})

add_subdirectory(${CMAKE_SOURCE_DIR}/pingo)
include_directories(pingo)
target_link_libraries(${PROJECT_NAME} pingo)


if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
else ()
    target_link_libraries("${PROJECT_NAME}"  ${SDL2_LIBRARIES})
endif ()



