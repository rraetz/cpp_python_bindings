# Set required CMake standard
cmake_minimum_required(VERSION 3.14)  # Updated minimum required version for better compatibility with pybind11

# Set required C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set name, version, and language of the project
project(example VERSION 1.0.0 LANGUAGES CXX)

# Add preprocessor definitions here if desired
add_definitions(-DMY_DEFINITION)  # Corrected spacing

# Define paths
set(INCLUDE_DIR include)
set(PLOG_INCLUDE_DIR libs/plog/include)

# Find libraries
find_package(Threads REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${PLOG_INCLUDE_DIR})

# Pybind11
set(PYBIND11_FINDPYTHON ON)
add_subdirectory(libs/pybind11)

# Define the module to be built with pybind11
pybind11_add_module(${PROJECT_NAME} src/main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall -O3>
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /O3>
)

set(DESTINATION_DIR ${CMAKE_SOURCE_DIR}/export)

# Set up installation directory
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})


# Assuming pybind11-stubgen is installed and available
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=$<TARGET_FILE_DIR:${PROJECT_NAME}> pybind11-stubgen ${PROJECT_NAME} --output-dir=${DESTINATION_DIR}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating .pyi file for ${PROJECT_NAME}"
)