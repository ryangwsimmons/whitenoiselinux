cmake_minimum_required(VERSION 3.6)
project(WhiteNoiseLinux VERSION 2.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Core Gui Widgets DBus REQUIRED)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/config.h")

find_package(PkgConfig REQUIRED)
pkg_check_modules(TagLib REQUIRED IMPORTED_TARGET taglib)
pkg_check_modules(PortAudio REQUIRED IMPORTED_TARGET portaudio-2.0)
pkg_check_modules(SndFile REQUIRED IMPORTED_TARGET sndfile)

include_directories(
    .
)

set (SRCS
    logo.svg
    logo_square.svg
    main.cpp
    resources_WhiteNoiseLinux.qrc
    WhiteNoiseLinux.supp
    wnlaboutdialog.cpp
    wnlaboutdialog.h
    wnlaboutdialog.ui
    wnlmainwindow.cpp
    wnlmainwindow.h
    wnlmainwindow.ui
    wnlmprismediaplayer2adaptor.cpp
    wnlmprismediaplayer2adaptor.h
    wnlmprismediaplayer2playeradaptor.cpp
    wnlmprismediaplayer2playeradaptor.h
    wnlmprismetadatamap.cpp
    wnlmprismetadatamap.h
    wnlplaybackmanager.cpp
    wnlplaybackmanager.h
    wnlplaylist.h
    wnlplaylistmanager.cpp
    wnlplaylistmanager.h
    wnlsound.h
    wnlsoundgrabber.cpp
    wnlsoundgrabber.h
)


add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus PkgConfig::TagLib PkgConfig::PortAudio PkgConfig::SndFile)
