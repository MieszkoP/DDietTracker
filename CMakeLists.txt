cmake_minimum_required(VERSION 3.5)

project(DDietTracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/home/mieszko/Qt/5.15.2/gcc_64/lib/cmake/Qt5" ${CMAKE_PREFIX_PATH})
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        size_unc.cpp
        size_unc.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DDietTracker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DDietTracker APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DDietTracker SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DDietTracker
            ${PROJECT_SOURCES}
            product.h product.cpp
            productcategory.h productcategory.cpp
            productserializer.h productserializer.cpp
            abstract_serializer.h abstract_serializer.cpp
            productdeserializer.h productdeserializer.cpp
            abstract_deserializer.h abstract_deserializer.cpp
            productcreator.h productcreator.cpp
            ddt.h ddt.cpp
            allproductsbase.h allproductsbase.cpp
            apbaseserializer.h apbaseserializer.cpp
            apbasedeserializer.h apbasedeserializer.cpp
            eatenproduct.h eatenproduct.cpp
            eatenday.h eatenday.cpp
            eatenproductserializer.h eatenproductserializer.cpp
            eatenproductdeserializer.h eatenproductdeserializer.cpp
            eatendayserializer.h eatendayserializer.cpp
            eatendaydeserializer.h eatendaydeserializer.cpp

            chartkcaloriescreator.h chartkcaloriescreator.cpp
            daytable.h daytable.cpp

            allproductstable.h allproductstable.cpp
            abstracttable.h abstracttable.cpp

            addeatenproductwindow.h addeatenproductwindow.cpp addeatenproductwindow.ui
            addtobasewindow.h addtobasewindow.cpp addtobasewindow.ui

        )
    endif()
endif()

target_link_libraries(DDietTracker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DDietTracker)
endif()
set_target_properties(DDietTracker PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DDietTracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DDietTracker)
endif()

set(CMAKE_PREFIX_PATH "~/vcpkg/packages/jsoncpp_x64-linux" ${CMAKE_PREFIX_PATH})

find_package(jsoncpp CONFIG REQUIRED)
include_directories(${jsoncpp_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets Charts)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Charts)
