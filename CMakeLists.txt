cmake_minimum_required(VERSION 3.20)
project(proxima VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/O2 /arch:AVX2)
else()
    add_compile_options(-O3 -march=native)
endif()

add_library(proxima_lib
        src/vector_store.cpp
)

target_include_directories(proxima_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(proxima src/main.cpp)

target_link_libraries(proxima PRIVATE proxima_lib)