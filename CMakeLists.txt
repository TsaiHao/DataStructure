cmake_minimum_required(VERSION 2.8)

project(myVector)
include_directories(./include)
file(GLOB SOURCES "src/main.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
