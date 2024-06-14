#include <stdio.h>
#include <stdlib.h>

#include "headers/huffman_compressing.h"

int main() {
    char* str = (char*)(malloc(sizeof(char) * 1000000));
    printf("Input your string: ");
    scanf("%[^\n]s",str);
    buildHuffmanTree(str);
    free(str);
    return 0;
}
