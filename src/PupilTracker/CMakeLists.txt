cmake_minimum_required(VERSION 3.3)

project (PupilTracker)


IF(WIN32)
  message("Windows platform detected...")
  set(PUPIL_TRACKER_ROOT "../${CMAKE_CURRENT_SOURCE_DIR}")


  ELSE(WIN32)
  message("Windows not detected...")
  set(PUPIL_TRACKER_ROOT "../${CMAKE_CURRENT_SOURCE_DIR}")

  ENDIF(WIN32)

#add_executable(PupilTracker PupilTracker.cxx)