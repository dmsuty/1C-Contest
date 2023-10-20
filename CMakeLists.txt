cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(compare_dirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(compare_dirs src/main.cpp src/dist.cpp src/find_similar_files.cpp)

# Must be pre-installed
find_package(OpenSSL REQUIRED)

# Add include directories for OpenSSL
target_include_directories(compare_dirs PRIVATE ${OPENSSL_INCLUDE_DIR})

# Link against OpenSSL library
target_link_libraries(compare_dirs PRIVATE ${OPENSSL_LIBRARIES})

# Fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# Link against argparse library
target_link_libraries(compare_dirs PRIVATE argparse)
