cmake_minimum_required(VERSION 3.24)
project(AliCompressor LANGUAGES C VERSION 1.0)

set(CMAKE_C_STANDARD 23)

set(SOURCES
        main.c
        src/priority_queue.c
        src/huffman_compressing.c
        src/node.c
        src/binary_tree.c)

add_executable(AliCompressor ${SOURCES})
