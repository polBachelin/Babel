cmake_minimum_required(VERSION 3.17)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# QT
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(NAME Babel)

project(${NAME}
LANGUAGES CXX
VERSION 0.1
DESCRIPTION "The new skype"
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()



#Client

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
file(GLOB_RECURSE SRC_CLIENT ${PROJECT_SOURCE_DIR}/client/src/*)
add_executable(babel_client ${SRC_CLIENT})

#QT lib

include_directories(${CMAKE_INCLUDE_PATH})
target_include_directories(babel_client BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/client/include)
target_include_directories(babel_client BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/client/include/pages)

target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Network Qt5::Widgets)

if (MVSVC)
        target_compile_options(babel_client PRIVATE /W4 /WX)
else ()
        target_compile_options(babel_client PRIVATE -Wall -Wextra -std=c++11)
endif()
