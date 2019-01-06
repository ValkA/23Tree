cmake_minimum_required(VERSION 3.13)
project(BalancedTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(BalancedTree main_tst.cpp LCRS_BalancedTree.cpp LCRS_BalancedTree.h Node.cpp Node.h LeafNode.cpp LeafNode.h InnerNode.cpp InnerNode.h )