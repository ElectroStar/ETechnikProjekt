#============================================================================
# @file CMakeLists.txt
# @brief CMake Liste zur Erstellung des Transmission-Service-Programms
#
# Diese CMake Liste ueberprueft ob die Abhaenigkeiten fuer das 
# Transmission-Service-Programms vorhanden sind. Es kommpiliert das 
# Transmission-Service-Programm und verknuepft es mit den entsprechenden 
# Bibilotheken.
#
# @author : Sebastian Hollermann
#============================================================================
cmake_minimum_required (VERSION 2.8.11)
project (Transmissionservice)
 
# Sourcen-Verzeichnis
add_subdirectory(src)
