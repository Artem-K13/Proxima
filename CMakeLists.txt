   cmake_minimum_required(VERSION 3.20)
   project(proxima)

   set(CMAKE_CXX_STANDARD 20)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)

   # Включаем оптимизации для скорости
   if(MSVC)
       add_compile_options(/O2 /arch:AVX2)
   else()
       add_compile_options(-O3 -march=native)
   endif()

   add_executable(proxima main.cpp)