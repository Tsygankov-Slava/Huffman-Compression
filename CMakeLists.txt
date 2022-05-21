cmake_minimum_required(VERSION 3.20)
project(Huffman_Compression)

set(CMAKE_CXX_STANDARD 17)

add_executable(Huffman_Compression src/main.cpp src/CLI/CLI.cpp src/CLI/CLI.h src/File/File.cpp src/File/File.h src/Tree/Tree.cpp src/Tree/Tree.h src/Queue/Queue.cpp src/Queue/Queue.h)
