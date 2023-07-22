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

set(VERSION_H_PATH "${PROJECT_SOURCE_DIR}/include/version.h")
set(VERSION_H_IN_PATH "${PROJECT_SOURCE_DIR}/version.h.in")

# Remove old version.h
if (EXISTS ${VERSION_H_PATH})
  message(STATUS "Removing old version.h")
  file(REMOVE ${VERSION_H_PATH})
endif()

# Generate version.h
configure_file(${VERSION_H_IN_PATH} ${VERSION_H_PATH})

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

aux_source_directory(./src SRC)
include_directories(./include ./third_party/cxxopts/include ./third_party/toml11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(${PROJECT_NAME} ${SRC})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
