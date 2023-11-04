set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
cmake_minimum_required(VERSION 2.8.3)
project(twinlitenet_dnn)

find_package(OpenCV 4.8.0)

# Options
option(ENABLE_CUDA "Enable CUDA" ON)

if(ENABLE_CUDA)
  message(STATUS "CUDA is enabled")
  add_definitions(-DENABLE_CUDA)
endif()

set(HEADER_FILES
  include/twinlitenet_dnn.hpp)
set(SOURCE_FILES
  src/main.cpp
  src/twinlitenet_dnn.cpp)

# general Includes
include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
)

# CUDA Includes
if(ENABLE_CUDA)
  find_package(CUDA REQUIRED)
  include_directories(
    ${CUDA_INCLUDE_DIRS})
endif()

add_executable(main ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(main
  ${OpenCV_LIBS})

if(ENABLE_CUDA)
  target_link_libraries(main
    ${CUDA_LIBRARIES})
endif()