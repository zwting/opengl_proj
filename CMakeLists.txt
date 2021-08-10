cmake_minimum_required(VERSION 3.10)
include(ExternalProject)

project(cmake_learn)

# Source files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(SOURCES
        src/main.cpp
        src/core/App.cpp
        src/core/Time.cpp
        src/core/Input.cpp
        src/constant/KeyCode.h
        src/utils/Debug.h
        src/utils/Debug.cpp
        src/core/Shader.h
        src/core/Shader.cpp
        src/core/Texture.h
        src/core/Texture.cpp
        src/core/Camera.h
        src/core/Camera.cpp
        src/core/Node.h
        src/core/Node.cpp
        src/core/Time.h
        src/core/Time.cpp
        src/utils/CommonUtils.h
        src/utils/CommonUtils.cpp
        )

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# glfw
add_library(glfw3 STATIC IMPORTED)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    message("clang compiler")
    set(glfw_lib_name ${LIB_DIR}/glfw/mac/libglfw.3.3.dylib)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("gnu compiler")
    set(glfw_lib_name ${LIB_DIR}/glfw/mingw/x32/libglfw3.a)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("msvc cimpiler")
    set(glfw_lib_name ${LIB_DIR}/glfw/msvc/glfw3.lib)
else ()
    set(glfw_lib_name ${LIB_DIR}/glfw/mingw/x32/libglfw3.a)
endif ()

set_target_properties(glfw3 PROPERTIES
        IMPORTED_LOCATION ${glfw_lib_name}
        )
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR}/glfw/include)


# glad
set(GLAD_DIR ${LIB_DIR}/glad)
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PRIVATE ${GLAD_DIR}/include)

# spdlog
ExternalProject_Add(spdlog
    PREFIX spdlog
    SOURCE_DIR ${LIB_DIR}/spdlog
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_INSTALL_PREFIX= ${STARING_DIR}
    -DSPDLOG_BUILD_SHARED=OFF
)
add_dependencies(${PROJECT_NAME} spdlog)

# glm
add_subdirectory(${LIB_DIR}/glm)
target_link_libraries(${PROJECT_NAME} glm::glm)

target_include_directories(${PROJECT_NAME} PUBLIC  
    ${GLAD_DIR}/include
    ${LIB_DIR}/stb
    ${LIB_DIR}/spdlog/include/
    ${SRC_DIR}/header
    ${LIB_DIR}/assimp
)


target_link_libraries(${PROJECT_NAME} glad glfw3)
