#============================================================================
# @file CMakeLists.txt
# @brief CMake Liste zur Erstellung des Clientprogramms
#
# Diese CMake Liste ueberprueft ob die Abhaenigkeiten fuer das 
# Clientprogramm vorhanden sind. Es kommpiliert das Clientprogramm
# und verknuepft es mit den entsprechenden Bibilotheken.
#
# @author : Sebastian Hollermann
#============================================================================
cmake_minimum_required(VERSION 2.8.11)

project(client)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Automoc für die CPP-Dateien
set(CMAKE_AUTOMOC ON)

# Erforderliche Pakte pruefen
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(OpenCV REQUIRED)

# Alle Sourcen und Header Dateien
set(SOURCE_FILES
	main.cpp
	mainwindow.h
	mainwindow.cpp
	posdata.h
	posdata.cpp
	positioningreceiver.h
	positioningreceiver.cpp
	imageupdater.h
	guifunctionclasses/player.h
	guifunctionclasses/converter.h
	guifunctionclasses/ModelCreator.h
	imageupdater.cpp
	guifunctionclasses/converter.cpp
	guifunctionclasses/ModelCreator.cpp
)

# Alle UI-Dateien
set(UI_FILES
	mainwindow.ui
)

# Header-Dateien aus den UI-Dateien erstellen
QT5_WRAP_UI(UI_HEADERS ${UI_FILES})

# Programm erstellen lassen
add_executable(eagleeye ${SOURCE_FILES} ${UI_HEADERS} ${UI_FILES})

# Programm mit den entsprechenden Bibilotheken verknuepfen lasse
target_link_libraries(eagleeye Qt5::Widgets Qt5::Network Qt5::Gui Qt5::Core ${OpenCV_LIBS})

# Programm ins Installationsverzeichnis schieben
install(TARGETS eagleeye DESTINATION ${Install_Dir})
