cmake_minimum_required(VERSION 3.18)
project(Sandbox)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

#Other Projects includes
include_directories("${Permafrost_SOURCE_DIR}/include")

#Sandbox Files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

#Sandbox Binary
add_executable(Sandbox ${HEADERS} ${SOURCES})
set_property(TARGET Sandbox PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
target_link_libraries(Sandbox Permafrost)