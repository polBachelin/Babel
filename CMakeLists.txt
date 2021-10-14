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

set(NAME Babel_server)
set(NAME_CLI Babel_client)
#set(NAME_SERV Babel_server)

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

#QT lib

#Include Client

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}")
configure_file(${PROJECT_SOURCE_DIR}/lib/configFile.babel ${CMAKE_BINARY_DIR}/bin/configFile.babel COPYONLY)

include_directories(./include/)
include_directories(./include/DLLoader/)
include_directories(./include/Sound)
include_directories(./include/Parser)
include_directories(./include/Server)
include_directories(./include/WindowsEquivalent)
include_directories(./src/Exception)
include_directories(./src/Exception/Error)

set(SRCS
    src/main.cpp
    src/Sound/CircularBuffer.cpp
    src/Sound/DecodedSound.cpp
    src/Exception/Error/Error.cpp
    src/Parser/ConfigFileParser.cpp
    )

add_executable(${NAME} ${SRCS})
target_link_libraries(${NAME} ${CONAN_LIBS})
target_include_directories(${NAME} PUBLIC CONAN_INCLUDE_DIRS)

#Client

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(./include/client)
include_directories(./include/client/Commands)
include_directories(./include/client/GUI/pages)
include_directories(./include/client/GUI/)
include_directories(./include/client/Network/)
include_directories(./include/client/Commands/)

set(SRCS_CLI
    src/client/main.cpp
    src/client/Commands/CommandsFactory.cpp
    src/client/GUI/pages/APage.cpp
    src/client/GUI/pages/LoginPage.cpp
    src/client/GUI/pages/RegisterPage.cpp
    src/client/GUI/pages/CallPage.cpp
    src/client/GUI/pages/ContactPage.cpp
    src/client/GUI/pages/PageManager.cpp
    src/client/GUI/MainWindow.cpp
    src/client/Network/TcpClient.cpp
    src/client/BabelClient.cpp
    src/client/Network/UdpClient.cpp
    src/client/Commands/CallManager.cpp
    )

add_executable(${NAME_CLI} ${SRCS_CLI})
target_link_libraries(${NAME_CLI} ${CONAN_LIBS} Qt5::Network Qt5::Widgets)
target_include_directories(${NAME_CLI} PUBLIC CONAN_INCLUDE_DIRS)

#PortAudio Lib
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Sound)
set(SOUND_DIR ${PROJECT_SOURCE_DIR}/lib/Sound)
include_directories(${SOUND_DIR})
include_directories(${SOUND_DIR}/Exception)
target_link_libraries(${NAME} Babel_PortAudio)
target_link_libraries(${NAME_CLI} Babel_PortAudio)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Encode)
set(ENCODE_DIR ${PROJECT_SOURCE_DIR}/lib/Encode)
include_directories(${ENCODE_DIR})
include_directories(${ENCODE_DIR}/Exception)
target_link_libraries(${NAME} Babel_Opus)
target_link_libraries(${NAME_CLI} Babel_Opus)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Server)
set(SERVER_DIR ${PROJECT_SOURCE_DIR}/lib/Server)
include_directories(${SERVER_DIR})
target_link_libraries(${NAME} Babel_Asio)
target_link_libraries(${NAME_CLI} Babel_Asio)

#Compilation 
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

if(WIN32)
        target_compile_options(${NAME} PRIVATE)
else()
        target_compile_options(${NAME} PRIVATE)
endif()
