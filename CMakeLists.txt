cmake_minimum_required(VERSION 3.14)

project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra)
endif()

add_executable(task1
    "main1.cpp"
    "src/train.cpp"
    "src/train_list.cpp"
)
target_include_directories(task1 PRIVATE "include/")

add_executable(task2 "main2.cpp")
