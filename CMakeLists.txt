cmake_minimum_required(VERSION 3.13)
project(demo)

# Get all files in the source directory recursively
file(GLOB_RECURSE SRC "demo/*.cpp" "demo/*.c")
file(GLOB_RECURSE LIB "ser/*.cpp" "ser/*.c")

# Create an executable using those source file
add_executable(${PROJECT_NAME} ${SRC} ${LIB})
target_include_directories(${PROJECT_NAME} PRIVATE "./")

# Specify that the C++ version to use for the executable is C++17
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /std:c++17)
    target_link_libraries(${PROJECT_NAME} PRIVATE setupapi.lib)
else (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -std=c++17)
endif (MSVC)

target_include_directories(${PROJECT_NAME} PRIVATE "lib/")

