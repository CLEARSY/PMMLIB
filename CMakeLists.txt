cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(BPARSERS)

if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  set(PROJECT_IS_TOP_LEVEL TRUE)
else()
  set(PROJECT_IS_TOP_LEVEL FALSE)
endif()

if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
endif()

add_subdirectory(extern)
add_subdirectory(src)
if(PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()

