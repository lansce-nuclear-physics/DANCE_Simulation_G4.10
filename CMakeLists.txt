
#////////////////////////////////////////////////////////////////////////
#//                                                                    //
#//   Software Name: DANCE Data Acquisition and Analysis Package       //
#//     Subpackage: DANCE_Simulation_G4.9                              //
#//   Identifying Number: C18105                                       // 
#//                                                                    //
#////////////////////////////////////////////////////////////////////////
#//                                                                    //
#//                                                                    //
#// Copyright 2019.                                                    //
#// Triad National Security, LLC. All rights reserved.                 //
#//                                                                    //
#//                                                                    //
#//                                                                    //
#// This program was produced under U.S. Government contract           //
#// 89233218CNA000001 for Los Alamos National Laboratory               //
#// (LANL), which is operated by Triad National Security, LLC          //
#// for the U.S. Department of Energy/National Nuclear Security        //
#// Administration. All rights in the program are reserved by          //
#// Triad National Security, LLC, and the U.S. Department of           //
#// Energy/National Nuclear Security Administration. The Government    //
#// is granted for itself and others acting on its behalf a            //
#// nonexclusive, paid-up, irrevocable worldwide license in this       //
#// material to reproduce, prepare derivative works, distribute        //
#// copies to the public, perform publicly and display publicly,       //
#// and to permit others to do so.                                     //
#//                                                                    //
#// This is open source software; you can redistribute it and/or       //
#// modify it under the terms of the GPLv2 License. If software        //
#// is modified to produce derivative works, such modified             //
#// software should be clearly marked, so as not to confuse it         //
#// with the version available from LANL. Full text of the GPLv2       //
#// License can be found in the License file of the repository         //
#// (GPLv2.0_License.txt).                                             //
#//                                                                    //
#////////////////////////////////////////////////////////////////////////


#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(DANCE_Simulation_G4.10)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------                                                                                                                  
# Find AIDA (optional package)                                                                                                                                                                 
#                                                                                                                                                                                              
find_package(AIDA)
if(AIDA_FOUND)
  add_definitions(-DG4ANALYSIS_USE)
endif()

#----------------------------------------------------------------------------                                                                                                                  
# Find ROOT (optional package)                                                                                                                                                                 
#                                                                                                                                                                                              
find_package(ROOT)
if(ROOT_FOUND)
  add_definitions(-DG4ANALYSIS_USE_ROOT)
endif()

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
include_directories(${PROJECT_SOURCE_DIR}/include
  ${Geant4_INCLUDE_DIR}
  ${AIDA_INCLUDE_DIR}
  ${ROOT_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(DICEBOX_DANCE DICEBOX_DANCE.cc ${sources} ${headers})
target_link_libraries(DICEBOX_DANCE ${Geant4_LIBRARIES} ${AIDA_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(DICEBOX_DANCE_SCRIPTS
  Co60.mac
  Y88.mac
  SG4900keV.mac
  vis.mac
  )

foreach(_script ${DICEBOX_DANCE_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(DANCE_Simulation_G4.10 DEPENDS DICEBOX_DANCE)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS DICEBOX_DANCE DESTINATION bin)


