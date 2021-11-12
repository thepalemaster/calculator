cmake_minimum_required(VERSION 3.5)

project(area_calc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(CORE_SOURCES
        #main.cpp
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
        src/console/console_literals.cpp
)
     

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(area_calc
        MANUAL_FINALIZATION
        ${CORE_SOURCES}
    )
else()
    if(ANDROID)
        add_library(area_calc SHARED
            ${CORE_SOURCES}
        )
    else()
        add_executable(area_calc
            ${CORE_SOURCES}
            ${CONSOLE_VIEW_SOURCES}
            ${PARSER_SOURCES}
        )
    endif()
endif()

set_target_properties(area_calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER palemaster.area_calc.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)


target_include_directories(area_calc PRIVATE hdr)
target_link_libraries(area_calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(area_calc)
endif()
