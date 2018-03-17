set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

cmake_minimum_required (VERSION 2.8.11)
project (JavaCompilerFlex)

find_package(FLEX)

FLEX_TARGET(MyScanner test.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
#include_directories("D:/Program Files (x86)/GnuWin32/include")
#LINK_DIRECTORIES("D:/Program Files (x86)/GnuWin32/lib")

#add_library(libfl SHARED IMPORTED)
#set_property(TARGET libfl PROPERTY IMPORTED_LOCATION "D:/Program Files (x86)/GnuWin32/lib/libfl.a")

add_executable(LexicalAnalyzerFlex
    ${FLEX_MyScanner_OUTPUTS}
)
TARGET_LINK_LIBRARIES(LexicalAnalyzerFlex fl)














#include_directories("C:/Program Files (x86)/GnuWin32/include")
# LINK_DIRECTORIES("C:/Program Files (x86)/GnuWin32/lib")
# find_library(FOO_LIB libfl)
# LIST(APPEND CMAKE_FIND_LIBRARY_SUFFIXES ".a")
# TARGET_LINK_LIBRARIES(LexicalAnalyzerFlex libfl)
# add_library( libfl SHARED IMPORTED )
# set_target_properties( libfl PROPERTIES IMPORTED_LOCATION "C:/Program Files (x86)/GnuWin32/lib/libfl.a" )
