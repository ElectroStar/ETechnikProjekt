#============================================================================
# @file CMakeLists.txt
# @brief CMake Liste zur Erstellung des EagleEye-Projektes
#
# Diese CMake Liste uebernimmt die Konfiguration zur Erstellungen der
# einzelnen Programmen des EagleEye-Projektes.
#
# @author : Sebastian Hollermann
#============================================================================

cmake_minimum_required (VERSION 2.8.11)
project (EagleEye)

# Optionen
# Doxygen
OPTION(WITH_DOXYGEN  "Dokumentation generieren"  OFF)

# Client erstellen
OPTION(CLIENT "Client erstellen" OFF)

# Transmission Service erstellen
OPTION(SERVICE "Transmission-Service erstellen" OFF)

OPTION(SERVER "Server erstellen lassen" OFF)

# Wenn Alle Optionen aus sind alle auf Anstellen
IF(NOT ${CLIENT} AND NOT ${SERVICE} AND NOT ${SERVER})
	set(CLIENT ON)
	set(SERVICE ON)
	set(SERVER ON)
ENDIF()

# Installationsverzeichnis setzen 
set(Install_Dir ${PROJECT_SOURCE_DIR}/bin)

# Client Verzeichnis
if(${CLIENT})
	# GUI-Elemente sowie Network von Qt5 sind Vorraussetzung
	find_package(Qt5Widgets REQUIRED)
	find_package(Qt5Core REQUIRED)
	find_package(Qt5Gui REQUIRED)
	find_package(Qt5Network REQUIRED)
	add_subdirectory(Client)
endif()

# Server Verzeichnis
if(${SERVER})
	# OpenCV sowie die GUI-Elemente von Qt5 sind Vorraussetzung
	find_package(Qt5Widgets REQUIRED)
	find_package(Qt5Core REQUIRED)
	find_package(Qt5Gui REQUIRED)
	find_package(OpenCV REQUIRED)
	add_subdirectory(qtProjekt/ServerGui)
endif()

# Transmission-Service Verzeichnis
if(${SERVICE})
	# PThreads suchen, ist Vorraussetzung	
	find_package(Threads REQUIRED)

	add_subdirectory(Transmission_Service)
endif()

# Doxygen Erstellung
if(${WITH_DOXYGEN})
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
          configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
          add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
    endif(DOXYGEN_FOUND)
endif()
