cmake_minimum_required(VERSION 3.18)
project(Sandbox)

#Other Projects includes
include_directories("${Permafrost_SOURCE_DIR}/include")

#Sandbox Files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

#Sandbox Binary
add_executable(Sandbox ${HEADERS} ${SOURCES})
target_link_libraries(Sandbox Permafrost)