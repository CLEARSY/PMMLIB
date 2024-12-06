cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

include(FetchContent)

FetchContent_Declare(
  coco_r
  GIT_REPOSITORY https://github.com/CLEARSY/coco_r.git
)

FetchContent_GetProperties(coco_r)

if(NOT coco_r_POPULATED)
  FetchContent_Populate(coco_r)
  message(STATUS "coco_r_SOURCE_DIR: ${coco_r_SOURCE_DIR}")
  message(STATUS "coco_r_BINARY_DIR: ${coco_r_BINARY_DIR}")
  add_subdirectory(
    ${coco_r_SOURCE_DIR}
    ${coco_r_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()
