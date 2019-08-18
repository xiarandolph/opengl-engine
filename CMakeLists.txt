cmake_minimum_required(VERSION 3.1)

project(opengl-engine)

include_directories(include)

set(SOURCES
    ./src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# GLFW
set(GLFW_DIR ./extlibs/glfw-3.3)
# set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL Build the GLFW example programs)
# set(GLFW_BUILD_TESTS OFF CACHE INTERNAL Build the GLFW test programs)
# set(GLFW_BUILD_DOCS OFF CACHE INTERNAL Build the GLFW documentation)
# set(GLFW_INSTALL OFF CACHE INTERNAL Generate installation target)
add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

# glad
set(GLAD_DIR ./extlibs/glad)
add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)
target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS})
