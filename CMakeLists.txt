cmake_minimum_required(VERSION 3.5)

project(area_calc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(CORE_SOURCES
    src/calculator.cpp
    src/shape_areas.cpp
    src/shapes.cpp
    src/result.cpp
    src/model/shape_model.cpp
    src/model/iterator.cpp
)

set(PARSER_SOURCES
    src/parser/parser.cpp
)

set(CONSOLE_VIEW_SOURCES
    src/console/console_view.cpp
    src/console/main_console.cpp
    src/console/shape_info.cpp
)

set(QTWIDGETS_SOURCES
    src/qtwidgets/main_qtwidgets.cpp
    src/qtwidgets/area_view.cpp
    src/qtwidgets/calculator_window.cpp
    src/qtwidgets/shape_view.cpp
    src/qtwidgets/shape_options.cpp
    src/qtwidgets/shape_buttons.cpp
    src/qtwidgets/shape_list.cpp
    src/qtwidgets/shape_input.cpp
    hdr/qtw/shape_view.hpp
    src/qtwidgets/modal_options.cpp
    hdr/qtw/modal_option.hpp
)
  
add_library(calculator STATIC
    src/calculator.cpp
    src/shape_areas.cpp
    src/shapes.cpp
    src/result.cpp
)

add_library(parser STATIC
    src/parser/parser.cpp
)

add_library(shape_model STATIC
    src/model/shape_model.cpp
    src/model/iterator.cpp
)


add_executable(area_calc
        ${CONSOLE_VIEW_SOURCES}
)

add_executable(qt_area_calc
      ${QTWIDGETS_SOURCES}
)

target_link_libraries(qt_area_calc PRIVATE 
    calculator
    parser
    shape_model
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(area_calc PRIVATE 
    calculator
    parser
    shape_model
)

target_include_directories(calculator PUBLIC hdr)
target_include_directories(parser PUBLIC hdr)
target_include_directories(shape_model PUBLIC hdr)
target_include_directories(area_calc PRIVATE hdr)
target_include_directories(qt_area_calc PUBLIC hdr/qtw)
        

set_target_properties(area_calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER palemaster.area_calc.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
