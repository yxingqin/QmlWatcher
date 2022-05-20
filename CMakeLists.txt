cmake_minimum_required(VERSION 3.21.1)

project(QmlWatcher)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(GLOB_RECURSE   SRCS  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  LIST_DIRECTORIES false 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    )
LIST(APPEND SRCS "qml/qml.qrc")


find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
    ${SRCS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
)
