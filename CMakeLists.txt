cmake_minimum_required(VERSION 3.6)
project(WhiteNoiseLinux VERSION 2.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets DBus Concurrent REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TagLib REQUIRED IMPORTED_TARGET taglib)
pkg_check_modules(PortAudio REQUIRED IMPORTED_TARGET portaudio-2.0)
pkg_check_modules(SndFile REQUIRED IMPORTED_TARGET sndfile)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/config.h")

include_directories(
    ./include
)

set(CMAKE_AUTOUIC_SEARCH_PATHS ./forms)

set(SOURCES
    ./src/main.cpp
    ./src/wnlaboutdialog.cpp
    ./src/wnlmainwindow.cpp
    ./src/wnlmprismediaplayer2adaptor.cpp
    ./src/wnlmprismediaplayer2playeradaptor.cpp
    ./src/wnlmprismetadatamap.cpp
    ./src/wnlplaybackmanager.cpp
    ./src/wnlplaylist.cpp
    ./src/wnlplaylistmanager.cpp
    ./src/wnlplaylistmanager.cpp
    ./src/wnlsound.cpp
    ./src/wnlsoundgrabber.cpp
)

set(UIS
    ./forms/wnlaboutdialog.ui
    ./forms/wnlmainwindow.ui
)

set(MOC_HEADERS
    ./include/wnlaboutdialog.h
    ./include/wnlmainwindow.h
    ./include/wnlmprismediaplayer2adaptor.h
    ./include/wnlmprismediaplayer2playeradaptor.h
    ./include/wnlmprismetadatamap.h
    ./include/wnlplaybackmanager.h
    ./include/wnlplaylist.h
    ./include/wnlplaylistmanager.h
    ./include/wnlsound.h
    ./include/wnlsoundgrabber.h
)

set(RESOURCES
    ./res/resources_WhiteNoiseLinux.qrc
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${MOC_HEADERS} ${UIS} ${RESOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus Qt5::Concurrent PkgConfig::TagLib PkgConfig::PortAudio PkgConfig::SndFile)
