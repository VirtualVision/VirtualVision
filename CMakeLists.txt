cmake_minimum_required(VERSION 2.8)
#Official Top-level CMakeLists!!!!
project (VirtualVision)

if (WIN32)
	message("Setting Root Directories For Windows")
	set(THIRDPARTY "C:/ThirdParty")
	set(OPENCV_ROOT "${THIRDPARTY}/opencv")

	if (${ARCH_FLAG} STREQUAL "x64")
		message("Running CMake for Windows x64 Host System")
		set(OPENCV_BUILD_DIR "${OPENCV_ROOT}/build/x64/vc12")
		set(ZEROMQ_ROOT "${THIRDPARTY}/ZeroMQ 4.0.4_x64")
	endif(${ARCH_FLAG} STREQUAL "x64")
	if (${ARCH_FLAG} STREQUAL "x86")
		message("Running CMake for Windows x86 Host System")
		set(OPENCV_BUILD_DIR "${OPENCV_ROOT}/build/x86/vc12")
		set(ZEROMQ_ROOT "${THIRDPARTY}/ZeroMQ 4.0.4_x86")
	endif(${ARCH_FLAG} STREQUAL "x86")

	set(OPENCV_INCLUDE_DIRS "${OPENCV_ROOT}/build/include;${OPENCV_ROOT}/build/include/opencv;${OPENCV_ROOT}/build/include/opencv2")
	set(OPENCV_LIB_DIR "${OPENCV_BUILD_DIR}/lib")
	set(OPENCV_STATICLIB_DIR "${OPENCV_BUILD_DIR}/staticlib")

	set(ZEROMQ_BUILD_DIR "${ZEROMQ_ROOT}")
	set(ZEROMQ_BINARY_DIR "${ZEROMQ_ROOT}/bin")
	set(ZEROMQ_INCLUDE_DIR "${ZEROMQ_ROOT}/include")
	set(ZEROMQ_LIB_DIR "${ZEROMQ_ROOT}/lib")


	# find all of the libs in OPENCV_LIB_DIRS
	file(GLOB OpenCV_LIB
		RELATIVE ${OPENCV_LIB_DIR} ${OPENCV_LIB_DIR}/*.lib)		
	file(GLOB OpenCV_STATICLIB	
		RELATIVE ${OPENCV_STATICLIB_DIR} ${OPENCV_STATICLIB_DIR}/*.lib)

	# find all of the libs in ZEROMQ_LIB_DIR
	file(GLOB ZEROMQ_LIBS 
		RELATIVE "${ZEROMQ_LIB_DIR}" "${ZEROMQ_LIB_DIR}/*.lib")

	link_directories(
		"${OPENCV_LIB_DIR}"
		"${OPENCV_STATICLIB_DIR}" 
		"${ZEROMQ_LIB_DIR}")

	add_subdirectory (GazeFinder)
	add_subdirectory (PupilTracker)
	add_subdirectory (GameEnv)
	#add_subdirectory (Display)
	add_subdirectory (TestPub)
	add_subdirectory (TestSub)

	# add the executable
	add_executable(VirtualVision VirtualVision.cpp)

	target_link_libraries (VirtualVision 
		"${OpenCV_LIB}" 
		"${OpenCV_STATICLIB}"
		"${ZEROMQ_LIBS}")

endif(WIN32)

if(UNIX)
	message(STATUS "OS is Linux")
	message("Running CMake for Raspberry Pi Remote System")
	message("Setting Root Directories For Linux")

	IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
        IF(GCC_VERSION VERSION_LESS 4.7)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        ELSE()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        ENDIF()
    ELSE()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    ENDIF()

	include_directories("${PROJECT_BINARY_DIR}")
    find_package(Boost REQUIRED)
    find_package(PkgConfig)
    pkg_check_modules(ZeroMQ libzmq)
    find_library(ZMQ_LIB zmq)

	find_package(OpenCV REQUIRED)

	add_executable(swirski_tracker swirski_main.cpp)

	target_link_libraries(swirski_tracker ${ZMQ_LIB})

	add_library(swirski_lib swirski_pupil/PupilTracker.cpp swirski_pupil/cvx.cpp swirski_pupil/utils.cpp)
	target_link_libraries(swirski_tracker swirski_lib ${OpenCV_LIBS} tbb)

endif(UNIX)


# add the install targets
install (TARGETS VirtualVision DESTINATION bin)