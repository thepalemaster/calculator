cmake_minimum_required(VERSION 3.0)

set(projectName model_test)

project(${projectName} VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_C_COMPILER gсс)
set(CMAKE_CXX_COMPILER g++)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


add_executable(${projectName} 
    model_test.cpp
)

target_sources(${projectName} PRIVATE 
    ../../src/model/iterator.cpp 
    ../../src/model/shapemodel.cpp
)

target_include_directories(${projectName} PRIVATE ../../hdr)
