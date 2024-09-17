cmake_minimum_required(VERSION 3.10)
project(lab1)

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

add_executable(lab1 include/ClockConverter.h src/ClockConverter.cpp main.cpp)
target_include_directories(lab1 PRIVATE include)

# Добавление тестов
enable_testing()

add_executable(tests gtests/tests01.cpp include/ClockConverter.h src/ClockConverter.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)