cmake_minimum_required(VERSION 2.8)

project (VirtualVision)

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	if (WIN32)
		set(WINXXBITS Win64)
		message(STATUS "OS is Windows")
	    ########################################################################################
		###Target is 64 bits
		###Operating System is Windows

	    ########################################################################################
	elseif(WIN32)
        ########################################################################################
		###Target is 64 bits
		###Operating System is NOT Windows
		message(STATUS "OS is NOT Windows")

	    ########################################################################################
	endif(WIN32)
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
   message(STATUS "Target is 32 bits")
   if (WIN32)
        set(WINXXBITS Win32)
		message(STATUS "OS is Windows")
	    ########################################################################################
		###Target is 32 bits
		###Operating System is Windows

		set(THIRDPARTY "C:/ThirdParty")

		#Set OpenCV Environment Vars
		set(OPENCV_ROOT "${THIRDPARTY}/opencv")
		set(OPENCV_x86_BUILD_DIR "${OPENCV_ROOT}/build/x86/vc12")
		set(OPENCV_INCLUDE_DIRS "${OPENCV_ROOT}/build/include;${OPENCV_ROOT}/build/include/opencv;${OPENCV_ROOT}/build/include/opencv2")
		set(OPENCV_LIB_DIR "${OPENCV_x86_BUILD_DIR}/lib")
		set(OPENCV_STATICLIB_DIR "${OPENCV_x86_BUILD_DIR}/staticlib")

		#Set ZeroMQ Environment vars
		set(ZEROMQ_ROOT "${THIRDPARTY}/ZeroMQ 4.0.4_x86")
		set(ZEROMQ_BUILD_DIR "${ZEROMQ_ROOT}")
		set(ZEROMQ_BINARY_DIR "${ZEROMQ_ROOT}/bin")
		set(ZEROMQ_INCLUDE_DIR "${ZEROMQ_ROOT}/include")
		set(ZEROMQ_LIB_DIR "${ZEROMQ_ROOT}/lib")

		# add the binary tree to the search path for include files
		# so that we will find VirtualVisionConfig.h
		include_directories("${PROJECT_BINARY_DIR}")
		include_directories(${OPENCV_x86_BUILD_DIR})
		include_directories(${OPENCV_INCLUDE_DIRS})
		include_directories("${ZEROMQ_BINARY_DIR}")
		include_directories("${ZEROMQ_BUILD_DIR}")
		include_directories("${ZEROMQ_INCLUDE_DIR}")

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
		#add_subdirectory (UserDisplay)
		add_subdirectory (TestPub)
		add_subdirectory (TestSub)

		# add the executable
		add_executable(VirtualVision VirtualVision.cpp)

		target_link_libraries (VirtualVision 
			"${OpenCV_LIB}" 
			"${OpenCV_STATICLIB}"
			"${ZEROMQ_LIBS}")


	    ########################################################################################
   elseif(WIN32)
		########################################################################################
        #############Target is 32 bits
		###Operating System is NOT Windows
		message(STATUS "OS is NOT Windows")

		
		include_directories("${PROJECT_BINARY_DIR}")
		include_directories ("${PROJECT_SOURCE_DIR}/GazeFinder")

		find_package(OpenCV REQUIRED)
		find_package(PkgConfig)
		pkg_check_modules(ZeroMQ libzmq)
		find_library(ZMQ_LIB zmq)

		add_subdirectory (GazeFinder)

		add_executable(VirtualVision VirtualVision.cpp)

		target_link_libraries(VirtualVision
			${OpenCV_LIBS}
			${ZMQ_LIB})


	    ########################################################################################
	endif(WIN32)
endif("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")



# add the install targets
install (TARGETS VirtualVision DESTINATION bin)
