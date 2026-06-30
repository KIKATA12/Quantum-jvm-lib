cmake_minimum_required(VERSION 3.16)
project(quantum_jvm_lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(JNI REQUIRED)

include_directories(
  ${JNI_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/core
  ${CMAKE_CURRENT_SOURCE_DIR}/core/qubit
  ${CMAKE_CURRENT_SOURCE_DIR}/core/registers
)

file(GLOB REPO_SOURCES
  "core/**/*.cpp"
  "jni/*Bridge.cpp"
)

add_library(QubitNative SHARED ${REPO_SOURCES})
set_target_properties(QubitNative PROPERTIES
  PREFIX ""
  OUTPUT_NAME "QubitNative"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
)
