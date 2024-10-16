cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -s")
set(CMAKE_CXX_FLAGS "-std=gnu99")


# Set the project name
project(shm_writer)

# Add the executable
add_executable(${CMAKE_PROJECT_NAME} 
	src/main.c)
