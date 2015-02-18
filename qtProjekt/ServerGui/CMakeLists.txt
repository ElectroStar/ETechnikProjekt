#============================================================================
# @file CMakeLists.txt
# @brief CMake Liste zur Erstellung des Serverprogramms
#
# Diese CMake Liste ueberprueft ob die Abhaenigkeiten fuer das 
# Serverprogramm vorhanden sind. Es kommpiliert das Serverprogramm
# und verknuepft es mit den entsprechenden Bibilotheken.
#
# @author : Sebastian Hollermann
#============================================================================

cmake_minimum_required(VERSION 2.8.11)

project(server)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Automoc für die CPP-Dateien
set(CMAKE_AUTOMOC ON)

# Erforderliche Pakte pruefen
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(OpenCV REQUIRED)

# Alle Sourcen und Header Dateien
set(SOURCE_FILES
	main.cpp
    	gui/mainwindow.cpp
	gui/login.cpp
	gui/guiFunctionClasses/drawimage.cpp
    	gui/guiFunctionClasses/playerstream.cpp
    	gui/guiFunctionClasses/playertracking.cpp
    	gui/guiFunctionClasses/converter.cpp
    	gui/cameracalibrationdialog.cpp
    	model/Calibrator/Calibrator.cpp
    	model/Filters/Undistorter.cpp
    	gui/errordialog.cpp
    	gui/guiFunctionClasses/player.cpp
    	gui/guiFunctionClasses/playercalib.cpp
    	model/Exception/exception.cpp
    	gui/infoeagleeyedialog.cpp
    	model/PositionService/LocatableObject.cpp
    	model/PositionService/LocatedObject.cpp
    	model/PositionService/MetricPositionTransformator.cpp
    	model/PositionService/ObjectLocator.cpp
    	model/Filters/CropFieldView.cpp
    	model/FieldLocator/FieldLocator.cpp
    	model/Transmitter/PosData.cpp
    	model/Transmitter/Transmitter.cpp
    	gui/settingsdialog.cpp
    	Settings.cpp
	gui/mainwindow.h
    	gui/login.h
    	gui/guiFunctionClasses/drawimage.h
    	gui/guiFunctionClasses/playerstream.h
    	gui/guiFunctionClasses/playertracking.h
    	gui/guiFunctionClasses/converter.h
    	gui/cameracalibrationdialog.h
    	model/Calibrator/Calibrator.h
    	model/Filters/ImageFilter.h
    	model/Filters/Undistorter.h
    	gui/errordialog.h
    	gui/guiFunctionClasses/player.h
    	gui/guiFunctionClasses/playercalib.h
    	model/Exception/exception.h
    	gui/infoeagleeyedialog.h
    	model/PositionService/IPositionService.h
    	model/PositionService/LocatableObject.h
    	model/PositionService/LocatedObject.h
    	model/PositionService/MetricPositionTransformator.h
    	model/PositionService/ObjectLocator.h
    	model/Filters/CropFieldView.h
    	model/FieldLocator/FieldLocator.h
    	model/Transmitter/ConnectionException.h
    	model/Transmitter/PosData.h
    	model/Transmitter/PositioningDataException.h
    	model/Transmitter/Transmitter.h
    	model/Transmitter/TransmittingException.h
    	gui/settingsdialog.h
    	Settings.h
)

# Alle UI-Dateien
set(UI_FILES
	gui/mainwindow.ui
    	gui/login.ui
    	gui/cameracalibrationdialog.ui
    	gui/errordialog.ui
    	gui/infoeagleeyedialog.ui
    	gui/settingsdialog.ui
)

# Header-Dateien aus den UI-Dateien erstellen
QT5_WRAP_UI(UI_HEADERS ${UI_FILES})

# Code fuer die Resourcen erstellen
qt5_add_resources(RESOURCE_FILES gui/image.qrc)

# Programm erstellen lassen
add_executable(server ${SOURCE_FILES} ${UI_HEADERS} ${UI_FILES} ${RESOURCE_FILES})

# Programm mit den entsprechenden Bibilotheken verknuepfen lasse
target_link_libraries(server Qt5::Widgets Qt5::Gui Qt5::Core ${OpenCV_LIBS})

# Programm ins Installationsverzeichnis schieben
install(TARGETS server DESTINATION ${Install_Dir})
