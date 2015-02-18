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

# Abhaenigkeiten ueberpruefen
find_package(Threads REQUIRED)

# Source Dateien
set(serviceSrcs
	Condition.cpp
	Mutex.cpp
	Networkinterface.cpp
	PosData.cpp
	Thread.cpp
	Service.cpp
	TCPServer.cpp
	TCPStream.cpp
	UDPSender.cpp
	TCPReceiver.cpp
	TCPConnector.cpp
	main.cpp
	)

# Programm erstellen lassen
add_executable(transmissionservice ${serviceSrcs})

# Programm mit den benoetigten Bibilotheken verknuefen lassen
target_link_libraries(transmissionservice ${CMAKE_THREAD_LIBS_INIT})

# Programm in das Installationsverzeichnis verschieben
install(TARGETS transmissionservice DESTINATION ${Install_Dir})
