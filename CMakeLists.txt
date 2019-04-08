cmake_minimum_required(VERSION 3.6)
project(drawpad)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR  ON)
set (CMAKE_PREFIX_PATH "path->/Users/xuhao/tools/Qt5.7.0/5.7/clang_64")
#打开Qt的MOC功能和UI文件处理功能
set(CMAKE_AUTOMOC on)
set(CMAKE_AUTOUIC on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#查找Qt的库
find_package(Qt5Widgets REQUIRED)
INCLUDE_DIRECTORIES(/Users/xuhao/tools/eigen)

set(SOURCE_FILES
        Source/main.cpp
        Header/mainwindow.h
        Source/PaintWidget.cpp
        Header/PaintWidget.h
        Entity/Node.cpp
        Entity/Node.h
        Entity/Edge.cpp
        Entity/Edge.h
        Entity/Util.cpp
        Force/ExternalForce.h
        Force/Force.h
        Shape/Arrow.cpp
        Shape/Arrow.h
        Data/Data.cpp
        )

add_executable(drawpad ${SOURCE_FILES})

target_link_libraries(drawpad Qt5::Widgets)