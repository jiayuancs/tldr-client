cmake_minimum_required(VERSION 3.2)

# Extract major, minor and patch version from package.json
file(READ "package.json" PACKAGE_JSON)
string(REGEX MATCH "\"version\": \"([0-9]+)\.([0-9]+)\.([0-9]+)\"" VERSION_MATCH ${PACKAGE_JSON})
if(NOT VERSION_MATCH)
  message(FATAL_ERROR "Failed to parse version from package.json")
endif()

message(STATUS "Version ${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}")

project(
  tldr
  VERSION ${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}
  LANGUAGES CXX)

# Generate version.h
configure_file(
  "${PROJECT_SOURCE_DIR}/version.h.in"
  "${PROJECT_SOURCE_DIR}/include/version.h")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)

aux_source_directory(./src SRC)
include_directories(./include ./third_party/cxxopts/include)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(${PROJECT_NAME} ${SRC})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
