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
set(NAME_CLI Babel_client)
set(NAME_SERV Babel_server)

project(${NAME}
LANGUAGES CXX
VERSION 0.1
DESCRIPTION "The new skype"
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

#Client
# ---------------------------------------
find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
file(GLOB_RECURSE SRC_CLIENT ${PROJECT_SOURCE_DIR}/client/src/*)
add_executable(${NAME_CLI} ${SRC_CLIENT})

#QT lib

include_directories(${CMAKE_INCLUDE_PATH})
target_include_directories(${NAME_CLI} BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/client/include)
target_include_directories(${NAME_CLI} BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/client/include/GUI/pages)
target_include_directories(${NAME_CLI} BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/client/include/GUI/)

target_link_libraries(${NAME_CLI} ${CONAN_LIBS} Qt5::Network Qt5::Widgets)

#Server
# ---------------------------------------
include_directories(./include/DLLoader/)
include_directories(./include/Sound)
include_directories(./include/Parser)
include_directories(./include/Server)
include_directories(./src/Exception)
include_directories(./src/Exception/Error)

set(SRCS
    src/main.cpp
    src/Sound/CircularBuffer.cpp
    src/Sound/DecodedSound.cpp
    src/Exception/Error/Error.cpp
    src/Parser/ConfigFileParser.cpp)


set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}")

configure_file(${PROJECT_SOURCE_DIR}/lib/configFile.babel ${CMAKE_BINARY_DIR}/bin/configFile.babel COPYONLY)
add_executable(${NAME} ${SRCS})
# ---------------------------------------

# set(SRCS_CLI
#     src/client/main.cpp)

# add_executable(${NAME_CLI} ${SRCS_CLI})
# target_link_libraries(${NAME_CLI} PUBLIC ${CONAN_LIBS})
# target_include_directories(${NAME_CLI} PUBLIC CONAN_INCLUDE_DIRS)
# target_include_directories(${NAME_CLI} PUBLIC ${PROJECT_SOURCE_DIR}/includes)
# target_include_directories(${NAME_CLI} PUBLIC ${PROJECT_SOURCE_DIR}/includes/Server)

if (MVSVC)
        target_compile_options(babel_client PRIVATE /W4 /WX)
else ()
        target_compile_options(${NAME} PRIVATE -Wall -Wextra -std=c++17)
endif()

#PortAudio Lib
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Sound ${PROJECT_BINARY_DIR}/BabelLibs/Sound)
#set(SOUND_DIR ${PROJECT_SOURCE_DIR}/lib/Sound)
#include_directories(${SOUND_DIR}/)
#target_link_libraries(${NAME} Babel_PortAudio)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Encode ${PROJECT_BINARY_DIR}/BabelLibs/Encode)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Server ${PROJECT_BINARY_DIR}/BabelLibs/Server)

target_link_libraries(${NAME} ${CONAN_LIBS})
target_include_directories(${NAME} PUBLIC CONAN_INCLUDE_DIRS)
