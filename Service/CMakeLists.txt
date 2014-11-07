cmake_minimum_required (VERSION 2.6)
project (Transmissionservice)
# Versionsnummer
set (Transmissionservice_VERSION_MAJOR 0)
set (Transmissionservice_VERSION_MINOR 9)
 
# PThreads suchen, ist Vorraussetzung
find_package(Threads REQUIRED)
 
# Sourcen-Verzeichnis
add_subdirectory(src)
