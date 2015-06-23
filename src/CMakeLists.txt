cmake_minimum_required(VERSION 2.8)

project (VirtualVision)

IF(WIN32)
  message("VirtualVision detects Windows platform...")

  #Set Windows Root 
  #FIXME... this is hard coded!!!!!!!
  set(VIRTUAL_VISION_ROOT "C:/VirtualVision")
  set(VIRTUAL_VISION_SRC "${VIRTUAL_VISION_ROOT}/src")
  set(VIRTUAL_VISION_THIRDPARTY "${VIRTUAL_VISION_ROOT}/ThirdParty")

  #Set OpenCV Environment Vars
  set(OPENCV_ROOT "${VIRTUAL_VISION_THIRDPARTY}/Windows_x64/OpenCV")
  set(OPENCV_BUILD_DIR "${OPENCV_ROOT}/build/x64/vc12")
  set(OPENCV_INCLUDE_DIRS "${OPENCV_ROOT}/build/include;${OPENCV_ROOT}/build/include/opencv;${OPENCV_ROOT}/build/include/opencv2")
  set(OPENCV_LIB_DIRS "${OPENCV_ROOT}/build/x64/vc12/lib")
  set(OPENCV_STATICLIB_DIRS "${OPENCV_ROOT}/build/x64/vc12/staticlib")

  #Set ZeroMQ Environment vars
  set(ZEROMQ_ROOT "${VIRTUAL_VISION_THIRDPARTY}/Windows_x64/ZeroMQ_4.0.4")
  set(ZEROMQ_BUILD_DIR "${ZEROMQ_ROOT}")
  set(ZEROMQ_BINARY_DIR "${ZEROMQ_ROOT}/bin")
  set(ZEROMQ_INCLUDE_DIR "${ZEROMQ_ROOT}/include")
  set(ZEROMQ_LIB_DIR "${ZEROMQ_ROOT}/lib")

ELSE(WIN32)
  message("VirtualVision does not detect Windows platform...")
 
  #Set Linux Root 
  set(VIRTUAL_VISION_ROOT "/usr/VirtualVision")
  set(VIRTUAL_VISION_SRC "${VIRTUAL_VISION_ROOT}/src")
 
ENDIF(WIN32)

add_subdirectory (
    VirtualVisionMain)