cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(TestPMMLIB)

find_package(Qt5 REQUIRED COMPONENTS Core Test)

set(BPARSERS_TESTS_SRC
	MatchTests.cpp
	PmmParserTests.cpp
	WriteTests.cpp
	AttributesTests.cpp
)

if(APPLE)
	find_library(MAC_SECURITY
		NAMES Security)
	set(EXTRA_LIBRARIES ${MAC_SECURITY})
endif(APPLE)

qt5_wrap_cpp(BPARSERS_TESTS_MOC_SRC ${BPARSERS_TESTS_SRC})

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${PMMLIB_SOURCE_DIR})

add_executable(matchtests     MatchTests.cpp)
add_executable(pmmparsertests PmmParserTests.cpp)
add_executable(writetests     WriteTests.cpp)
add_executable(attributestests AttributesTests.cpp)

set_source_files_properties(AttributesTests.cpp
	PROPERTIES
	OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/moc_AttributesTests.cpp)
set_source_files_properties(MatchTests.cpp
	PROPERTIES
	OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/moc_MatchTests.cpp)
set_source_files_properties(PmmParserTests.cpp
	PROPERTIES
	OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/moc_PmmParserTests.cpp)
set_source_files_properties(WriteTests.cpp
	PROPERTIES
	OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/moc_WriteTests.cpp)

target_link_libraries(matchtests -Bstatic BPARSERS_LIB -Bdynamic Qt5::Core Qt5::Test ${EXTRA_LIBRARIES})
target_link_libraries(pmmparsertests -Bstatic BPARSERS_LIB -Bdynamic Qt5::Core Qt5::Test ${EXTRA_LIBRARIES})
target_link_libraries(writetests -Bstatic BPARSERS_LIB -Bdynamic Qt5::Core Qt5::Test ${EXTRA_LIBRARIES})
target_link_libraries(attributestests -Bstatic BPARSERS_LIB -Bdynamic Qt5::Core Qt5::Test ${EXTRA_LIBRARIES})

add_test(BPARSERS.MatchTest ${CMAKE_CURRENT_BINARY_DIR}/matchtests)
add_test(BPARSERS.PmmParser ${CMAKE_CURRENT_BINARY_DIR}/pmmparsertests)
add_test(BPARSERS.WriteTest ${CMAKE_CURRENT_BINARY_DIR}/writetests)
add_test(BPARSERS.AttributesTests ${CMAKE_CURRENT_BINARY_DIR}/attributestests)
