cmake_minimum_required(VERSION 3.7)
project(GroupMProject
        VERSION 1.0
        DESCRIPTION "Our final C++ Project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# encapsulate source files in variable
set(SOURCES
        src/main.cpp
        src/InputHandler.cpp
        src/Simulation.cpp
        src/Writer.cpp
        src/Body.cpp
        )

# encapsulate source files in variable
set (HEADERS
        include/InputHandler.hpp
        include/Simulation.hpp
        include/Writer.hpp
        include/Body.hpp include/Vector2D.hpp include/GeneralParameters.hpp include/EulerIntegrator.hpp include/Units.hpp include/DataPoint.hpp)



add_executable(nBodySim ${SOURCES} ${HEADERS})

################Documentation###############
option(BUILD_DOCS "Build documentation" OFF)
if(BUILD_DOCS)
    add_subdirectory(docs)
endif()