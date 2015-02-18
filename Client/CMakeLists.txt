cmake_minimum_required(VERSION 2.8.11)

project(client)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Automoc für die CPP-Dateien
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

SET(client_SOURCES main.cpp mainwindow.cpp posdata.cpp positioningreceiver.cpp)
SET(client_HEADERS mainwindow.h posdata.h positioningreceiver.h)
SET(client_FORMS mainwindow.ui)

set(SOURCE_FILES
	main.cpp
	mainwindow.h
	mainwindow.cpp
	posdata.h
	posdata.cpp
	positioningreceiver.h
	positioningreceiver.cpp
)

set(UI_FILES
	mainwindow.ui
)

QT5_WRAP_UI(UI_HEADERS ${UI_FILES})

add_executable(eagleeye ${SOURCE_FILES} ${UI_HEADERS} ${UI_FILES})

target_link_libraries(eagleeye Qt5::Widgets Qt5::Network Qt5::Gui Qt5::Core)

install(TARGETS eagleeye DESTINATION ${Install_Dir})
