cmake_minimum_required(VERSION 3.5)

project(area_calc VERSION 0.5 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets Svg REQUIRED)

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
    src/qtwidgets/measure_units.cpp
    hdr/qtw/measure_units.hpp
    src/qtwidgets/inputnumberqvalidator.cpp
    hdr/qtw/inputnumberqvalidator.hpp
    src/qtwidgets/utility_measure_units_qt.cpp
    res/resourses.qrc
)

set(QML_SOURCES
        src/qml/main.cpp
        src/qml/qml.qrc
        hdr/qml/shape_list_model.hpp
        src/qml/shape_list_model.cpp
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
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(empty
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_add_executable(qml_calc
        MANUAL_FINALIZATION
        ${QML_SOURCES}
    )
else()
    add_executable(qt_area_calc
        ${QTWIDGETS_SOURCES}
    )

    add_executable(qml_calc
        ${QML_SOURCES}
    )
endif()

add_executable(area_calc
    ${CONSOLE_VIEW_SOURCES}
)

target_link_libraries(qt_area_calc PRIVATE 
    calculator
    parser
    shape_model
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
)

target_link_libraries(qml_calc PRIVATE
    calculator
    shape_model
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
)

target_link_libraries(area_calc PRIVATE 
    calculator
    parser
    shape_model
)

if(LANGUAGE_FOR_BUILD STREQUAL "eng")
    target_compile_definitions(qt_area_calc PRIVATE LANG_ENG)
    target_compile_definitions(shape_model PRIVATE LANG_ENG)
    target_compile_definitions(area_calc PRIVATE LANG_ENG)
endif()

target_include_directories(calculator PUBLIC hdr)
target_include_directories(parser PUBLIC hdr)
target_include_directories(shape_model PUBLIC hdr)
target_include_directories(area_calc PRIVATE hdr)
target_include_directories(qt_area_calc PRIVATE hdr/qtw)
target_include_directories(qml_calc PRIVATE hdr/qml)
        
set_target_properties(area_calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER palemaster.area_calc.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

target_compile_definitions(qml_calc
   PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

set_target_properties(qml_calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER qml.area_calc.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(qml_calc)
    qt_finalize_executable(qml_calc)
endif()
