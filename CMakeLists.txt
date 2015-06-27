cmake_minimum_required(VERSION 3.3)

project (VirtualVision)

# The version number.
set (VirtualVision_VERSION_MAJOR 1)
set (VirtualVision_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/VirtualVisionConfig.h.in"
  "${PROJECT_BINARY_DIR}/VirtualVisionConfig.h"
  )

IF(WIN32)
set(THIRDPARTY "C:/ThirdParty")

#Set OpenCV Environment Vars
set(OPENCV_ROOT "${THIRDPARTY}/Windows_x64/OpenCV")
set(OPENCV_BUILD_DIR "${OPENCV_ROOT}/build/x64/vc12")
set(OPENCV_INCLUDE_DIRS "${OPENCV_ROOT}/build/include;${OPENCV_ROOT}/build/include/opencv;${OPENCV_ROOT}/build/include/opencv2")
set(OPENCV_LIB_DIRS "${OPENCV_ROOT}/build/x64/vc12/lib")
set(OPENCV_STATICLIB_DIRS "${OPENCV_ROOT}/build/x64/vc12/staticlib")

#Set ZeroMQ Environment vars
set(ZEROMQ_ROOT "${THIRDPARTY}/Windows_x64/ZeroMQ_4.0.4")
set(ZEROMQ_BUILD_DIR "${ZEROMQ_ROOT}")
set(ZEROMQ_BINARY_DIR "${ZEROMQ_ROOT}/bin")
set(ZEROMQ_INCLUDE_DIR "${ZEROMQ_ROOT}/include")
set(ZEROMQ_LIB_DIR "${ZEROMQ_ROOT}/lib")

# add the binary tree to the search path for include files
# so that we will find VirtualVisionConfig.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/CamControl")
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

add_subdirectory (CamControl)

# add the executable
add_executable(VirtualVision VirtualVision.cpp)

target_link_libraries (VirtualVision 
	"${OpenCV_LIBS}" 
	"${OpenCV_STATICLIBS}"
	"${ZEROMQ_LIBS}"
	CamControl)

ELSEIF(WIN32)
find_package(OpenCV REQUIRED)
find_package(PkgConfig)
pkg_check_modules(ZeroMQ libzmq)
find_library(ZMQ_LIB zmq)

add_subdirectory (CamControl)

add_executable(VirtualVision VirtualVision.cpp)

target_link_libraries(VirtualVision
	${OpenCV_LIBS}
	${ZMQ_LIB}
	CamControl)

ENDIF(WIN32)



# add the install targets
install (TARGETS VirtualVision DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/VirtualVisionConfig.h"        
         DESTINATION include)