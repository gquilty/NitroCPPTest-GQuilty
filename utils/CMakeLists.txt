cmake_minimum_required(VERSION 2.8.6)
MESSAGE( STATUS "******************************************")
# Set options for this project.
set (PROJECT_NAME "NitroCPPTest-GavinQuilty" CXX)
MESSAGE( STATUS "PROJECT NAME: " ${PROJECT_NAME})
MESSAGE( STATUS "******************************************")
project(${PROJECT_NAME})
set(CMAKE_BUILD_TYPE Release)
include (GenerateExportHeader)


#Bring the headers into the project
file(GLOB_RECURSE INCLUDES
         RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
         ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h)
         MESSAGE( STATUS "ADDED INCLUDES")
         MESSAGE( STATUS "******************************************")

#Bring the source
file(GLOB_RECURSE SOURCES
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp)
        MESSAGE( STATUS "ADDED SOURCES")
        MESSAGE( STATUS "******************************************")

IF(WIN32) # Check if we are on Windows
  if(MSVC) # Check if we  are using the Visual Studio compiler
      MESSAGE( STATUS "You are using windows and a MSVC Compiler")
      MESSAGE( STATUS "Setting MSVC flags")
      MESSAGE( STATUS "******************************************")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Alt to MSVC
  else()
    message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
  endif()
elseif(APPLE)
  # Nothing specified yet
elseif(UNIX)
    message(status "Setting GCC flags")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g -Wall")
    # Set the location for library installation. Use "sudo make install" to apply
    #install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib)
else()
  message(SEND_ERROR "Unsupported platform!")
ENDIF()
MESSAGE( STATUS "Flags: ${CMAKE_CXX_FLAGS}")
MESSAGE( STATUS "Flags successfully added:")
MESSAGE( STATUS "******************************************")

################################################################
##                      Building executable
#################################################################

#Generate Executable
# link_directories( ${CMAKE_BINARY_DIR}/bin)
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
