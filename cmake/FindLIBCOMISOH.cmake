# - Try to find the LIBCOMISO library
# Once done this will define
#
#  LIBCOMISO_FOUND - system has LIBCOMISO
#  LIBCOMISO_INCLUDE_DIR - the LIBCOMISO include directory
#  LIBCOMISO_LIBRARY - the LIBCOMISO binary lib

FIND_PATH(LIBCOMISO_INCLUDE_DIR CoMISo/Solver/ConstrainedSolver.hh
   /usr/include
   /usr/local/include
   $ENV{LIBCOMISOROOT}/include
   $ENV{LIBCOMISO_ROOT}/include
   $ENV{LIBCOMISO_DIR}/include
   $ENV{LIBCOMISO_DIR}/inc
   ${PROJECT_SOURCE_DIR}/../
   ${PROJECT_SOURCE_DIR}/../../
   ${PROJECT_SOURCE_DIR}/../../../
   ${PROJECT_SOURCE_DIR}/../CoMISo/
   ${PROJECT_SOURCE_DIR}/../CoMISo/include
   ${PROJECT_SOURCE_DIR}/../../CoMISo/
   ${PROJECT_SOURCE_DIR}/../../CoMISo/include
   /Users/daniele/Dropbox/igl/MIQ/src
   /Users/olkido/Documents/igl/MIQ/src
)

SET(LIBCOMISO_FOUND "NO")
IF (COMISO_INCLUDE_DIR)
	SET(LIBCOMISO_FOUND "YES")
ENDIF (COMISO_INCLUDE_DIR)



if(LIBCOMISO_INCLUDE_DIR)

   #message("${LIBCOMISO_INCLUDE_DIR}")

   set(LIBCOMISO_INCLUDE_DIRS
      ${LIBCOMISO_INCLUDE_DIR}
      ${LIBCOMISO_INCLUDE_DIR}/CoMISo
      ${LIBCOMISO_INCLUDE_DIR}/CoMISo/Solver
      ${LIBCOMISO_INCLUDE_DIR}/CoMISo/EigenSolver
      ${LIBCOMISO_INCLUDE_DIR}/CoMISo/NSolver
      ${LIBCOMISO_INCLUDE_DIR}/CoMISo/Config
      ${LIBCOMISO_INCLUDE_DIR}/CoMISo/Utils
      ${LIBCOMISO_INCLUDE_DIR}/CoMISo/QtWidgets
      ${LIBCOMISO_INCLUDE_DIR}/CoMISo/ext/gmm-4.2/include
      )

   #message("${LIBCOMISO_INCLUDE_DIRS}")

   set(LIBCOMISO_INCLUDE_DIR ${LIBCOMISO_INCLUDE_DIR})

   add_definitions(-DINCLUDE_TEMPLATES)
   message(STATUS "Found LIBCOMISO: ${LIBCOMISO_INCLUDE_DIR}")
   set(LIBCOMISO_FOUND TRUE)
else(LIBCOMISO_INCLUDE_DIR)
  if(NOT LIBCOMISOH_FIND_QUIETLY)
   message(FATAL_ERROR "could NOT find LIBCOMISO")
 endif (NOT LIBCOMISOH_FIND_QUIETLY)
endif(LIBCOMISO_INCLUDE_DIR)
