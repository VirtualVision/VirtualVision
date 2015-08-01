cmake_minimum_required(VERSION 2.8)

project (GazeFinder)

IF(WIN32)

include_directories(${OPENCV_x86_BUILD_DIR})
include_directories(${OPENCV_INCLUDE_DIRS})
include_directories("${ZEROMQ_BINARY_DIR}")
include_directories("${ZEROMQ_BUILD_DIR}")
include_directories("${ZEROMQ_INCLUDE_DIR}")

set(HEADERS
  GazeFinder.h
  Calibrator.h
  Mapper.h
  PubSocket.h
  Logger.h

)
set(SOURCE
  GazeFinder.cpp
  Calibrator.cpp
  Mapper.cpp
  PubSocket.cpp
  Logger.cpp

)

add_executable(GazeFinder ${SOURCE} ${HEADERS})

target_link_libraries (GazeFinder
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
  GazeFinder.h
  Calibrator.h
  Mapper.h
  PubSocket.h
  Logger.h

)
set(SOURCE
    GazeFinder.cpp
  Calibrator.cpp
  Mapper.cpp
  PubSocket.cpp
  Logger.cpp

)

add_executable(GazeFinder ${SOURCE} ${HEADERS})

target_link_libraries(GazeFinder
	${OpenCV_LIBS}
	${ZMQ_LIB})

ENDIF(WIN32)
#####################################################################
install (TARGETS GazeFinder DESTINATION bin)
install (FILES GazeFinder.h DESTINATION include)
