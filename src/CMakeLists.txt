project(PMMLIB)

# Rule for regenerating the parser in the case where description files
# changes
add_custom_command(
	OUTPUT
		${BPARSERS_SOURCE_DIR}/src/pmmparser/Parser.cpp ${BPARSERS_SOURCE_DIR}/src/pmmparser/Parser.h
	    ${BPARSERS_SOURCE_DIR}/src/pmmparser/Scanner.cpp ${BPARSERS_SOURCE_DIR}/src/pmmparser/Scanner.h
    COMMAND
		cococpp -namespace theory pmmparser/pmm.atg
    DEPENDS
		pmmparser/pmm.atg pmmparser/Parser.frame pmmparser/Scanner.frame
    WORKING_DIRECTORY
		${BPARSERS_SOURCE_DIR}/src
)

set(BPARSERS_SRC
	pmmparser/Parser.cpp
	pmmparser/PmmFactory.cpp
	pmmparser/PmmFile.cpp
	pmmparser/PmmParser.cpp
	pmmparser/Scanner.cpp
	pmmparser/TheoryNode.cpp
	pmmtree/BinaryOperator.cpp
	pmmtree/BNode.cpp
	pmmtree/ChildNode.cpp
	pmmtree/DefaultErrorHandler.cpp
	pmmtree/Error.cpp
	pmmtree/ErrorHandler.cpp
	pmmtree/Joker.cpp
	pmmtree/JokerInstanciation.cpp
	pmmtree/Jokerizer.cpp
	pmmtree/LeafNode.cpp
	pmmtree/NodeWriter.cpp
	pmmtree/StreamWriter.cpp
	pmmtree/UnaryOperator.cpp
	pmmtree/NodeAttribute.cpp
    pmmtree/ParenthesisAttribute.cpp
    pmmtree/TextPos.cpp
	pmmparser/Parser.frame
	pmmparser/Scanner.frame
	pmmparser/pmm.atg
)

set(BPARSERS_HEADERS common.h
	pmmparser/Parser.h
	pmmparser/PmmFactory.h
	pmmparser/PmmFile.h
	pmmparser/PmmParser.h
	pmmparser/Scanner.h
	pmmparser/TheoryNode.h
	pmmtree/BinaryOperator.h
	pmmtree/BNode.h
	pmmtree/ChildNode.h
	pmmtree/DefaultErrorHandler.h
	pmmtree/Error.h
	pmmtree/ErrorHandler.h
	pmmtree/Joker.h
	pmmtree/JokerInstanciation.h
	pmmtree/Jokerizer.h
	pmmtree/LeafNode.h
	pmmtree/NodeWriter.h
	pmmtree/StreamWriter.h
	pmmtree/UnaryOperator.h
	pmmtree/NodeAttribute.h
    pmmtree/ParenthesisAttribute.h
    pmmtree/TextPos.h
)

add_library(BPARSERS_LIB STATIC ${BPARSERS_SRC} ${BPARSERS_HEADERS})
set_target_properties(BPARSERS_LIB PROPERTIES PREFIX "lib" OUTPUT_NAME "BParsers")
target_compile_features(BPARSERS_LIB PUBLIC cxx_std_20)

if(COMPILER_WARNINGS_ARE_ERRORS)
	target_compile_options(BPARSERS_LIB PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
	)
else(COMPILER_WARNINGS_ARE_ERRORS)
	target_compile_options(BPARSERS_LIB PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:/W4>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
	)
endif(COMPILER_WARNINGS_ARE_ERRORS)

include_directories(${PMMLIB_SOURCE_DIR})
if(WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

if(CMAKE_COMPILER_IS_GNUCXX)
  # Disable some warnings for generated code
  set_source_files_properties(pmmparser/Scanner.cpp
    pmmparser/Parser.cpp
    COMPILE_FLAGS "-Wno-parentheses"
    )
endif(CMAKE_COMPILER_IS_GNUCXX)
