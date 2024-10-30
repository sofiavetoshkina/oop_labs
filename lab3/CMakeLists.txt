cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

add_executable(lab3 include/vertex.h include/triangle.h include/figure.h include/square.h include/rectangle.h
src/vertex.cpp src/triangle.cpp src/square.cpp src/rectangle.cpp 
main.cpp)
target_include_directories(lab3 PRIVATE include)

