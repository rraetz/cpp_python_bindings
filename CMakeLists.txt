# Set required CMake standard
cmake_minimum_required(VERSION 3.0)


# Set required C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set name, version and language of project
project(haptic_robot VERSION 1.0.0 LANGUAGES CXX)


# Add preprocessor definitions here if desired
add_definitions(-D MY_DEFINTION)


# Define paths
set(INCLUDE_DIR include) 
set(PLOG_INCLUDE_DIR libs/plog/include)

 
# Find libraries 
find_package(Threads REQUIRED)


# Include directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${PLOG_INCLUDE_DIR})


# Add executables for main project
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/logging.cpp
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)


# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall -O3>
    $<$<CXX_COMPILER_ID:MSVC>: /W3 /O3>
    )



