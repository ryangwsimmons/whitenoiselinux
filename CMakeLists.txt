cmake_minimum_required(VERSION 3.6)
project(whitenoiselinux VERSION 2.0.2)

# Turn on all necessary processes for Qt to work
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Unless otherwise specified, set the default build type to release
if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
    endif()
endif()

# Ensure that Qt5 as well as all the required libraries are installed
find_package(Qt5 COMPONENTS Core Gui Widgets DBus Concurrent REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TagLib REQUIRED IMPORTED_TARGET taglib)
pkg_check_modules(PortAudio REQUIRED IMPORTED_TARGET portaudio-2.0)
pkg_check_modules(SndFile REQUIRED IMPORTED_TARGET sndfile)

# Set the configuration file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/config.h")

# Set the includes directory
include_directories(
    ./include
)

# Set the AUTOUIC search path so that forms are processed correctly
set(CMAKE_AUTOUIC_SEARCH_PATHS ./forms)

# Set variables for the different types of source files
set(SOURCES
    ${whitenoiselinux_SOURCE_DIR}/src/main.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlaboutdialog.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlattributionsdialog.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlmainwindow.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlmprismediaplayer2adaptor.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlmprismediaplayer2playeradaptor.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlmprismetadatamap.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlplaybackmanager.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlplaylist.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlplaylistmanager.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlplaylistmanager.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlsound.cpp
    ${whitenoiselinux_SOURCE_DIR}/src/wnlsoundgrabber.cpp
)

set(UIS
    ${whitenoiselinux_SOURCE_DIR}/forms/wnlaboutdialog.ui
    ${whitenoiselinux_SOURCE_DIR}/forms/wnlattributionsdialog.ui
    ${whitenoiselinux_SOURCE_DIR}/forms/wnlmainwindow.ui
)

set(MOC_HEADERS
    ${whitenoiselinux_SOURCE_DIR}/include/wnlaboutdialog.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlattributionsdialog.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlmainwindow.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlmprismediaplayer2adaptor.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlmprismediaplayer2playeradaptor.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlmprismetadatamap.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlplaybackmanager.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlplaylist.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlplaylistmanager.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlsound.h
    ${whitenoiselinux_SOURCE_DIR}/include/wnlsoundgrabber.h
)

set(RESOURCES
    ./res/resources_WhiteNoiseLinux.qrc
)

# Add the executable to the build, and link the executable with the required libraries
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${MOC_HEADERS} ${UIS} ${RESOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus Qt5::Concurrent PkgConfig::TagLib PkgConfig::PortAudio PkgConfig::SndFile)

# Define locations for installation
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION "bin")
install(DIRECTORY ${whitenoiselinux_SOURCE_DIR}/res/icons/ DESTINATION "share/icons/hicolor")
install(FILES ${whitenoiselinux_SOURCE_DIR}/res/whitenoiselinux.desktop DESTINATION "share/applications")
