cmake_minimum_required(VERSION 3.13)
project(Permafrost)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#Permafrost Dependencies
add_subdirectory("deps/Glad")
add_subdirectory("deps/GLFW")
add_subdirectory("deps/glm")
add_subdirectory("deps/spdlog")

#Permafrost Files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

#Permafrost Binary & Links
add_library(Permafrost STATIC ${HEADERS} ${SOURCES})
set_property(TARGET Permafrost PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
target_link_libraries(Permafrost Glad glfw ${GLFW_LIBRARIES} spdlog glm)

if(WIN32)
    target_link_libraries(Permafrost ws2_32 opengl32 gdi32)
endif()

#Permafrost PUBLIC API
target_include_directories(Permafrost PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

#Permafrost PRIVATE Dependencies
target_include_directories(Permafrost PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/deps/Glad/include")