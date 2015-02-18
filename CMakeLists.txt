cmake_minimum_required (VERSION 2.8.11)
project (EagleEye)

# Versionsnummer
set (Transmissionservice_VERSION_MAJOR 0)
set (Transmissionservice_VERSION_MINOR 9)

# Optionen
# Doxygen
OPTION(WITH_DOXYGEN  "Dokumentation generieren"  OFF)

# Client erstellen
OPTION(CLIENT "Client erstellen" OFF)

# Transmission Service erstellen
OPTION(SERVICE "Transmission-Service erstellen" OFF)

OPTION(SERVER "Server erstellen lassen" OFF)

# PThreads suchen, ist Vorraussetzung
find_package(Threads REQUIRED)

# DEFINITION : des preprocesseurs G++
#IF (CMAKE_COMPILER_IS_GNUCC)
#        ADD_DEFINITIONS(-O2 -Wall)
#ENDIF()

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
	add_subdirectory(Client)
endif()

# Transmission-Service Verzeichnis
if(${SERVICE})
	add_subdirectory(Transmission_Service)
endif()

# Doxygen
if(${WITH_DOXYGEN})
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
          configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
          add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
    endif(DOXYGEN_FOUND)
endif()
