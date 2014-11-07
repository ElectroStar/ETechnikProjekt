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

add_executable(transmissionservice ${serviceSrcs})

target_link_libraries(transmissionservice ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS transmissionservice
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
	ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib/static)
