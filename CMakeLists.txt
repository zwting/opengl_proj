cmake_minimum_required(VERSION 3.10)

project(cmake_learn)

# Source files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(SOURCES main.cxx src/App.cpp src/App.h src/core/Time.cpp src/core/Time.h src/design/Singleton.h)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# glfw
add_library(glfw3 SHARED IMPORTED)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    message("clang compiler")
    set(glfw_lib_name ${LIB_DIR}/glfw/mac/libglfw.3.3.dylib)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("gnu compiler")
    set(glfw_lib_name ${LIB_DIR}/glfw/mingw/x32/libglfw3.a)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("msvc cimpiler")
    set(glfw_lib_name ${LIB_DIR}/glfw/msvc/glfw3.lib)
else()
    set(glfw_lib_name ${LIB_DIR}/glfw/mingw/x32/libglfw3.a)
endif()

set_target_properties(glfw3 PROPERTIES
        IMPORTED_LOCATION ${glfw_lib_name}
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
        )
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR}/glfw/include)


# glad
set(GLAD_DIR ${LIB_DIR}/glad)
add_library(glad SHARED ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)
target_link_libraries(${PROJECT_NAME} glad glfw3)
