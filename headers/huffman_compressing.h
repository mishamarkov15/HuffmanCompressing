#ifndef ALICOMPRESSOR_HUFFMAN_COMPRESSING_H
#define ALICOMPRESSOR_HUFFMAN_COMPRESSING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "priority_queue.h"

void encode(node *root, const char *str, char **huffmanCode);

void decode(node *root, int *index, const char *str);

void buildHuffmanTree(const char *string);

#endif //ALICOMPRESSOR_HUFFMAN_COMPRESSING_H
