cmake_minimum_required(VERSION 2.8)

project (TestPub)

IF(WIN32)

include_directories(${OPENCV_x86_BUILD_DIR})
include_directories(${OPENCV_INCLUDE_DIRS})
include_directories("${ZEROMQ_BINARY_DIR}")
include_directories("${ZEROMQ_BUILD_DIR}")
include_directories("${ZEROMQ_INCLUDE_DIR}")

set(HEADERS
  TestPub.h
)
set(SOURCE
  TestPub.cpp
)

add_executable(TestPub ${SOURCE} ${HEADERS})

target_link_libraries (TestPub 
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
  TestPub.h
)
set(SOURCE
  TestPub.cpp
)

add_executable(TestPub ${SOURCE} ${HEADERS})

target_link_libraries(TestPub
	${OpenCV_LIBS}
	${ZMQ_LIB})

ENDIF(WIN32)
#####################################################################
install (TARGETS TestPub DESTINATION bin)
install (FILES TestPub.h DESTINATION include)