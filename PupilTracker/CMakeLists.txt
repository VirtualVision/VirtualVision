cmake_minimum_required(VERSION 2.8)

project (PupilTracker)

IF(WIN32)

include_directories(${OPENCV_x86_BUILD_DIR})
include_directories(${OPENCV_INCLUDE_DIRS})
include_directories("${ZEROMQ_BINARY_DIR}")
include_directories("${ZEROMQ_BUILD_DIR}")
include_directories("${ZEROMQ_INCLUDE_DIR}")

set(HEADERS
  PupilTracker.h
)
set(SOURCE
  PupilTracker.cpp
)

add_executable(PupilTracker ${SOURCE} ${HEADERS})

target_link_libraries (PupilTracker 
	"${OpenCV_LIB}" 
	"${OpenCV_STATICLIB}"
	"${ZEROMQ_LIBS}")

#####################################################################
ELSE(WIN32)

find_package(OpenCV REQUIRED)
find_package(PkgConfig)
pkg_check_modules(ZeroMQ libzmq)
find_library(ZMQ_LIB zmq)

set(HEADERS
  PupilTracker.h
)
set(SOURCE
  PupilTracker.cpp
)

add_executable(PupilTracker ${SOURCE} ${HEADERS})

target_link_libraries(PupilTracker
	${OpenCV_LIBS}
	${ZMQ_LIB})

ENDIF(WIN32)
#####################################################################
install (TARGETS PupilTracker DESTINATION bin)
install (FILES PupilTracker.h DESTINATION include)