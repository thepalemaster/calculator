cmake_minimum_required(VERSION 3.0)

set(projectName parcer_test)

project(${projectName} VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_C_COMPILER gсс)
set(CMAKE_CXX_COMPILER g++)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(parcer SHARED IMPORTED)



add_executable(${projectName} 
parcer_test.cpp
)

target_sources(parcer_test PRIVATE ../../src/result.cpp ../../src/parser/parser.cpp)

target_include_directories(parcer_test PRIVATE ../../hdr)
