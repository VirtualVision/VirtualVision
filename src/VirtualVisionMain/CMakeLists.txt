cmake_minimum_required(VERSION 2.8)

project (VirtualVisionMain)

set(VIRTUAL_VISION_MAIN "${CMAKE_CURRENT_SOURCE_DIR}")

IF(WIN32)
  message("VirtualVisionMain detects Windows platform...")
  include_directories(${OPENCV_BUILD_DIR})
  include_directories(${OPENCV_INCLUDE_DIRS})
  include_directories("${ZEROMQ_BINARY_DIR}")
  include_directories("${ZEROMQ_BUILD_DIR}")
  include_directories("${ZEROMQ_INCLUDE_DIR}")

        # find all of the libs in OPENCV_LIB_DIRS
	file(GLOB OpenCV_LIBS 
		RELATIVE ${OPENCV_LIB_DIRS} ${OPENCV_LIB_DIRS}/*.lib)		
	file(GLOB OpenCV_STATICLIBS 	
		RELATIVE ${OPENCV_STATICLIB_DIRS} ${OPENCV_STATICLIB_DIRS}/*.lib)

	# find all of the libs in ZEROMQ_LIB_DIR
	file(GLOB ZEROMQ_LIBS 
		RELATIVE "${ZEROMQ_LIB_DIR}" "${ZEROMQ_LIB_DIR}/*.lib")

	link_directories(
		"${OPENCV_LIB_DIRS}"
		"${OPENCV_STATICLIB_DIRS}" 
		"${ZEROMQ_LIB_DIR}")

	add_executable(VirtualVisionMain main.cpp)

	target_link_libraries(VirtualVisionMain 
		"${OpenCV_LIBS}" 
		"${OpenCV_STATICLIBS}"
		"${ZEROMQ_LIBS}")
  
ELSE(WIN32)
	message("VirtualVisionMain does not detect Windows platform...")

  find_package(OpenCV REQUIRED)
  find_package(PkgConfig)
  pkg_check_modules(ZeroMQ libzmq)
  find_library(ZMQ_LIB zmq)

  add_executable(VirtualVisionMain main.cpp) 

  target_link_libraries(VirtualVisionMain 
	${OpenCV_LIBS}
	${ZMQ_LIB})

ENDIF(WIN32)
