cmake_minimum_required(VERSION 3.28)

## Use the variable PROJECT_NAME for changing target name
set(PROJECT_NAME "Wildchain")
## Set compiler
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
## Set project name
project(${PROJECT_NAME} LANGUAGES CXX)

## Use all the .cpp files found under this folder for this project
FILE(GLOB SRCS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp" 
               "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

## Define Executable
add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} ssl crypto)
