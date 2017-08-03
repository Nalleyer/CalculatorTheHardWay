cmake_minimum_required(VERSION 3.8)
project(Calc)

set(CMAKE_CXX_STANDARD 17)

#set(SOURCE_FILES main.cpp lexer.cpp test_charType.cpp.test ast_node.cpp ast_node.h ast_visitor.cpp ast_visitor.h)
set(SOURCE_FILES main.cpp lexer.cpp)
add_executable(Calc ${SOURCE_FILES})