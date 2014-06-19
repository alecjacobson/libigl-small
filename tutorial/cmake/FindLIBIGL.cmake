# - Try to find the LIBIGL library
# Once done this will define
#
#  LIBIGL_FOUND - system has LIBIGL
#  LIBIGL_INCLUDE_DIR - the LIBIGL include directory
#  LIBIGL_SOURCES - the LIBIGL source files

FIND_PATH(LIBIGL_INCLUDE_DIR igl/readOBJ.h
   /usr/include
   /usr/local/include
   $ENV{LIBIGLROOT}/include
   $ENV{LIBIGL_ROOT}/include
   $ENV{LIBIGL_DIR}/include
   $ENV{LIBIGL_DIR}/inc
   ${PROJECT_SOURCE_DIR}/../libigl/include
   ${PROJECT_SOURCE_DIR}/../../libigl/include
   ${PROJECT_SOURCE_DIR}/../../include
)

if(LIBIGL_INCLUDE_DIR)
   set(LIBIGL_FOUND TRUE)
   set(LIBIGL_INCLUDE_DIR ${LIBIGL_INCLUDE_DIR}  ${LIBIGL_INCLUDE_DIR}/../external/Singular_Value_Decomposition)
   if(NOT LIBIGL_USE_STATIC_LIBRARY)
      add_definitions(-DIGL_HEADER_ONLY)
   endif(NOT LIBIGL_USE_STATIC_LIBRARY)
   #set(LIBIGL_SOURCES
   #   ${LIBIGL_INCLUDE_DIR}/igl/viewer/Viewer.cpp
   #)
endif(LIBIGL_INCLUDE_DIR)

if(LIBIGL_USE_STATIC_LIBRARY)
  set(LIBIGL_LIB_DIRS 
   /usr/lib
   /usr/local/lib
   $ENV{LIBIGLROOT}/lib
   $ENV{LIBIGL_ROOT}/lib
   $ENV{LIBIGL_DIR}/lib
   ${PROJECT_SOURCE_DIR}/../libigl/lib
   ${PROJECT_SOURCE_DIR}/../../libigl/lib
   ${PROJECT_SOURCE_DIR}/../../lib)
  FIND_LIBRARY( LIBIGL_LIBRARY NAMES igl PATHS ${LIBIGL_LIB_DIRS})
  if(NOT LIBIGL_LIBRARY)
    set(LIBIGL_FOUND FALSE)
  endif(NOT LIBIGL_LIBRARY)
  set(LIBIGL_LIBRARIES ${LIBIGL_LIBRARIES}  ${LIBIGL_LIBRARY})
  FIND_LIBRARY( LIBIGLMATLAB_LIBRARY NAMES iglmatlab PATHS ${LIBIGL_LIB_DIRS})
  if(NOT LIBIGLMATLAB_LIBRARY)
    set(LIBIGL_FOUND FALSE)
  endif(NOT LIBIGLMATLAB_LIBRARY)
  set(LIBIGL_LIBRARIES ${LIBIGL_LIBRARIES}  ${LIBIGLMATLAB_LIBRARY})
  FIND_LIBRARY( LIBIGLSVD3X3_LIBRARY NAMES iglsvd3x3 PATHS ${LIBIGL_LIB_DIRS})
  if(NOT LIBIGLSVD3X3_LIBRARY)
    set(LIBIGL_FOUND FALSE)
  endif(NOT LIBIGLSVD3X3_LIBRARY)
  set(LIBIGL_LIBRARIES ${LIBIGL_LIBRARIES}  ${LIBIGLSVD3X3_LIBRARY})
  FIND_LIBRARY( LIBIGLVIEWER_LIBRARY NAMES iglviewer PATHS ${LIBIGL_LIB_DIRS})
  if(NOT LIBIGLVIEWER_LIBRARY)
    set(LIBIGL_FOUND FALSE)
  endif(NOT LIBIGLVIEWER_LIBRARY)
  set(LIBIGL_LIBRARIES ${LIBIGL_LIBRARIES}  ${LIBIGLVIEWER_LIBRARY})
  find_package(OpenMP)
  if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  else(OPENMP_FOUND)
    set(LIBIGL_FOUND false)
  endif(OPENMP_FOUND)
endif(LIBIGL_USE_STATIC_LIBRARY)



if(LIBIGL_FOUND)
   if(NOT LIBIGL_FIND_QUIETLY)
      message(STATUS "Found LIBIGL: ${LIBIGL_INCLUDE_DIR}")
   endif(NOT LIBIGL_FIND_QUIETLY)
else(LIBIGL_FOUND)
   if(LIBIGL_FIND_REQUIRED)
      message(FATAL_ERROR "could NOT find LIBIGL")
   endif(LIBIGL_FIND_REQUIRED)
endif(LIBIGL_FOUND)

MARK_AS_ADVANCED(LIBIGL_INCLUDE_DIR LIBIGL_LIBRARIES IGL_VIEWER_SOURCES)
