cmake_minimum_required(VERSION 2.8)

project (Testub)

IF(WIN32)

include_directories(${OPENCV_x86_BUILD_DIR})
include_directories(${OPENCV_INCLUDE_DIRS})
include_directories("${ZEROMQ_BINARY_DIR}")
include_directories("${ZEROMQ_BUILD_DIR}")
include_directories("${ZEROMQ_INCLUDE_DIR}")

set(HEADERS
  TestSub.h
)
set(SOURCE
  TestSub.cpp
)

add_executable(TestSub ${SOURCE} ${HEADERS})

target_link_libraries (TestSub 
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
  TestSub.h
)
set(SOURCE
  TestSub.cpp
)

add_executable(TestSub ${SOURCE} ${HEADERS})

target_link_libraries(TestSub
	${OpenCV_LIBS}
	${ZMQ_LIB})

ENDIF(WIN32)
#####################################################################
install (TARGETS TestSub DESTINATION bin)
install (FILES TestSub.h DESTINATION include)