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
	controller/imageupdater.h
    	gui/errordialog.h
    	gui/infoeagleeyedialog.h
    	gui/mainwindow.h
    	gui/showimagedialog.h
    	model/receiver/posdata.h
    	model/receiver/positioningreceiver.h
    	model/converter.h
    	model/line.h
    	model/ModelCreator.h
	main.cpp
    	controller/imageupdater.cpp
    	gui/errordialog.cpp
    	gui/infoeagleeyedialog.cpp
    	gui/mainwindow.cpp
    	gui/showimagedialog.cpp
    	model/receiver/posdata.cpp
    	model/receiver/positioningreceiver.cpp
    	model/converter.cpp
    	model/line.cpp
    	model/ModelCreator.cpp
)

# Alle UI-Dateien
set(UI_FILES
	gui/errordialog.ui
    	gui/infoeagleeyedialog.ui
    	gui/mainwindow.ui
    	gui/showimagedialog.ui
)

# Header-Dateien aus den UI-Dateien erstellen
QT5_WRAP_UI(UI_HEADERS ${UI_FILES})

# Code fuer die Resourcen erstellen
qt5_add_resources(RESOURCE_FILES image.qrc)

# Programm erstellen lassen
add_executable(eagleeye ${SOURCE_FILES} ${UI_HEADERS} ${UI_FILES} ${RESOURCE_FILES})

# Programm mit den entsprechenden Bibilotheken verknuepfen lasse
target_link_libraries(eagleeye Qt5::Widgets Qt5::Network Qt5::Gui Qt5::Core ${OpenCV_LIBS})

# Programm ins Installationsverzeichnis schieben
install(TARGETS eagleeye DESTINATION ${Install_Dir})
