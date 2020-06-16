cmake_minimum_required(VERSION 3.18)
project(Permafrost)

#Permafrost Dependencies
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/deps/spdlog")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/deps/GLFW")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/deps/glm")

#Permafrost Files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

#Permafrost Binary & Links
add_library(Permafrost STATIC ${HEADERS} ${SOURCES})
target_link_libraries(Permafrost spdlog glm glfw ${GLFW_LIBRARIES})

#Permafrost PUBLIC API
target_include_directories(Permafrost PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")