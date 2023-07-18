cmake_minimum_required(VERSION 3.2)

project(tldr "CXX")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)

aux_source_directory(./src SRC)
include_directories(./include ./third_party/cxxopts/include)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(${PROJECT_NAME} ${SRC})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
