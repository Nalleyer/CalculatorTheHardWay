cmake_minimum_required(VERSION 3.5)
project(Calc)

#set(CMAKE_CXX_STANDARD 17)
add_compile_options(-std=c++17)

set(SOURCE_FILES main.cpp Lexer.cpp Parser.cpp ASTNode.cpp EvalVisitor.cpp )
#set(SOURCE_FILES main.cpp lexer.cpp)
add_executable(Calc ${SOURCE_FILES})
