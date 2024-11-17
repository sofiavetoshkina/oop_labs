cmake_minimum_required(VERSION 3.10)
project(lab5)

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

add_executable(lab5 include/memoryResource.h include/queue.h src/memoryResource.cpp
main.cpp)
target_include_directories(lab5 PRIVATE include)

# Добавление тестов
enable_testing()

add_executable(tests gtests/tests05.cpp include/memoryResource.h include/queue.h src/memoryResource.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)