cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(ParticleSwarmOptimization VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# find path to classes folder
set(INCLUDE_CLASSES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Classes" CACHE PATH "Path to classes")
set(PSO_SOURCES "main.cpp" "${INCLUDE_CLASSES_PATH}/ParticleSwarmOptimizer.h"
	"${INCLUDE_CLASSES_PATH}/ParticleSwarmOptimizer.cpp"
	"${INCLUDE_CLASSES_PATH}/Particle.h"
	"${INCLUDE_CLASSES_PATH}/Particle.cpp")



# add executable for C++ files
add_executable(test
			"${PSO_SOURCES}")


target_include_directories(test PRIVATE
						"${INCLUDE_CLASSES_PATH}")
