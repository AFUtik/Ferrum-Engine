cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME FerrumEngine)

project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)


file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL GLEW::GLEW ZLIB::ZLIB PNG::PNG glm::glm)

include(CTest)
enable_testing()

