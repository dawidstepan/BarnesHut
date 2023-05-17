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
        src/BarnesHutAlgorithm.cpp src/NaiveAlgorithm.cpp include/NaiveAlgorithm.hpp src/Integrator.cpp include/Integrator.hpp)

# encapsulate source files in variable
set (HEADERS
        include/InputHandler.hpp
        include/Simulation.hpp
        include/Writer.hpp
        include/Body.hpp include/Vector2D.hpp include/GeneralParameters.hpp include/BarnesHutAlgorithm.hpp src/NaiveAlgorithm.cpp include/NaiveAlgorithm.hpp src/Integrator.cpp include/Integrator.hpp)



add_executable(nBodySim ${SOURCES} ${HEADERS})

################Documentation###############
option(BUILD_DOCS "Build documentation" OFF)
if(BUILD_DOCS)
    add_subdirectory(docs)
endif()