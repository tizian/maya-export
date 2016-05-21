cmake_minimum_required(VERSION 2.8)

project(maya-export)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

if (MSVC)
  # Parallel build on MSVC (all targets)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

set(NAME "maya-export")

set(SOURCE_FILES
	"src/main.cpp"
)

set(FILE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/output")
configure_file("src/cmake_config.h.in" ${CMAKE_BINARY_DIR}/generated/cmake_config.h)
include_directories(${CMAKE_BINARY_DIR}/generated)

find_package(Maya REQUIRED)

include_directories(
	${MAYA_INCLUDE_DIR}
)

link_directories(${MAYA_LIBRARY_DIR})
add_library(${NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${NAME} ${MAYA_LIBRARIES})

MAYA_PLUGIN(${NAME})
install(TARGETS ${NAME} ${MAYA_TARGET_TYPE} DESTINATION plug-ins)
