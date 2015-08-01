cmake_minimum_required(VERSION 2.8)

project (Display)

IF(WIN32)

include_directories(${OPENCV_x86_BUILD_DIR})
include_directories(${OPENCV_INCLUDE_DIRS})
include_directories("${ZEROMQ_BINARY_DIR}")
include_directories("${ZEROMQ_BUILD_DIR}")
include_directories("${ZEROMQ_INCLUDE_DIR}")


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)


find_package(Qt5Widgets REQUIRED)


set(HEADERS
  Display.h
)
set(SOURCE
  Display.cpp
  main.cpp
)
set(FORMS
  Display.ui
)




add_executable(Display ${SOURCE} ${HEADERS} ${FORMS})

target_link_libraries (Display 
	"${OpenCV_LIB}" 
	"${OpenCV_STATICLIB}"
	"${ZEROMQ_LIBS}"
	Qt5::Widgets)

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

add_executable(Display ${SOURCE} ${HEADERS})

target_link_libraries(Display
	${OpenCV_LIBS}
	${ZMQ_LIB})

ENDIF(WIN32)
#####################################################################
install (TARGETS Display DESTINATION bin)
install (FILES Display.h DESTINATION include)