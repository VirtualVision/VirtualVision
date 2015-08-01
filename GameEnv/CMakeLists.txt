cmake_minimum_required(VERSION 2.8)

project (GameEnv)

IF(WIN32)

include_directories(${OPENCV_x86_BUILD_DIR})
include_directories(${OPENCV_INCLUDE_DIRS})
include_directories("${ZEROMQ_BINARY_DIR}")
include_directories("${ZEROMQ_BUILD_DIR}")
include_directories("${ZEROMQ_INCLUDE_DIR}")

set(HEADERS
  GameEnv.h
)
set(SOURCE
  GameEnv.cpp

)

add_executable(GameEnv ${SOURCE} ${HEADERS})

target_link_libraries (GameEnv 
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
  GameEnv.h
)
set(SOURCE
  GameEnv.cpp

)

add_executable(GameEnv ${SOURCE} ${HEADERS})

target_link_libraries(GameEnv
	${OpenCV_LIBS}
	${ZMQ_LIB})

ENDIF(WIN32)
#####################################################################
install (TARGETS GameEnv DESTINATION bin)
install (FILES GameEnv.h DESTINATION include)
