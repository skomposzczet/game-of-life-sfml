cmake_minimum_required(VERSION 3.1.0)
project (main)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(Map STATIC ${SOURCES})

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

target_link_libraries(${PROJECT_NAME} Map
  sfml-system 
  sfml-window 
  sfml-graphics
)

add_custom_target(run ./${PROJECT_NAME})