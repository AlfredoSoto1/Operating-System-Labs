cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "-std=gnu99")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-03 -DNDEBUG -s")

# Set the project name
project(cpu_sched)

# Include the current directory for header files
include_directories(include)

# Add the executable
add_executable(${CMAKE_PROJECT_NAME} 
	src/task_measurer.c
	src/main.c)

# target_link_libraries(${CMAKE_PROJECT_NAME})