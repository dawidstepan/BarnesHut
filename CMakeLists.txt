cmake_minimum_required(VERSION 3.7)
project(GroupMProject
        VERSION 1.0
        DESCRIPTION "Our final C++ Project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CONAN_DISABLE_CHECK_COMPILER TRUE CACHE BOOL "" FORCE )

set(PROJECT_ROOT_NAME ${PROJECT_NAME})
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})


# set default build type (Necessary for conan to work)
SET(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}'")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
      "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

################### DEPENDENCIES ################
# Download conan cmake config and use it to automatically fetch all required packages
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

# run conan install and create cmake targets
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt
                BUILD missing
                PROFILE default
                BASIC_SETUP CMAKE_TARGETS)

# include cmake_paths generator file to get package-supplied PackageConfig.cmake
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(SFML REQUIRED)

file(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

add_library(${PROJECT_NAME} SHARED ${CPP_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HPP_FILES}")
target_link_libraries(${PROJECT_NAME} PUBLIC SFML::graphics)

add_executable(nBodySim "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
target_link_libraries(nBodySim PUBLIC ${PROJECT_NAME})


################### TESTING #####################
# only include tests if the current project is being built
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

# if we are building the current project and tests should be built
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(test)
endif()

################Documentation###############
option(BUILD_DOCS "Build documentation" OFF)
if(BUILD_DOCS)
    add_subdirectory(docs)
endif()