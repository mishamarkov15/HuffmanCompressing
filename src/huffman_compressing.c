#include "../headers/huffman_compressing.h"

void encode(node *root, const char *str,
            char **huffmanCode) {
    if (root == NULL) {
        return;
    }

    if (!root->left && !root->right) {
        huffmanCode[(int) (root->letter)] = (char *) (malloc(sizeof(char) * strlen(str) + 1));
        strcpy(huffmanCode[(int) (root->letter)], str);
    }

    char *left = (char *) (malloc(sizeof(char) * strlen(str) + 2));
    strcpy(left, str);
    strcat(left, "0");
    encode(root->left, left, huffmanCode);
    free(left);

    char *right = (char *) (malloc(sizeof(char) * strlen(str) + 2));;
    strcpy(right, str);
    strcat(right, "1");
    encode(root->right, right, huffmanCode);
    free(right);
}

void decode(node *root, int *index, const char *str) {
    if (root == NULL) {
        return;
    }

    if (!root->left && !root->right) {
        printf("%c", root->letter);
        return;
    }

    (*index)++;

    if (str[*index] == '0') {
        decode(root->left, index, str);
    } else {
        decode(root->right, index, str);
    }
}

void buildHuffmanTree(const char *string) {
    // Count frequency of characters: index - code of symbol, value - frequency of this symbol
    const int alphabet_size = (1 << (sizeof(char) * 8)); // 1 << sizeof(char) * 8 <=> 1 << 8 <=> pow(2, 8)
    uint64_t* frequency = (uint64_t*)(calloc(alphabet_size, sizeof (uint64_t)));
    for (uint64_t i = 0; i < strlen(string); ++i) {
        ++frequency[(int) (string[i])];
    }

    // Priority queue
    priority_queue *pq = createQueue();
    for (int i = 0; i < alphabet_size; ++i) {
        if (frequency[i] > 0) {
            // priorityQueue Push
            insert(pq, createNode((char) (i), frequency[i]));
        }
    }

    while (pq->size != 1) {
        node *left = createNode(pq->data[0]->letter, pq->data[0]->frequency);
        left->left = pq->data[0]->left;
        left->right = pq->data[0]->right;
        deleteRoot(pq, pq->data[0]->letter);

        node *right = createNode(pq->data[0]->letter, pq->data[0]->frequency);
        right->left = pq->data[0]->left;
        right->right = pq->data[0]->right;
        deleteRoot(pq, pq->data[0]->letter);

        uint64_t sum = left->frequency + right->frequency;

        node *new_node = createNode('\0', sum);
        new_node->left = left;
        new_node->right = right;

        insert(pq, new_node);
    }

    node *root = pq->data[0];

    char **huffmanCode = (char **) (malloc(sizeof(char *) * alphabet_size));
    encode(root, "", huffmanCode);

    printf("Huffman Codes are:\n");
    for (int i = 0; i < alphabet_size; ++i) {
        if (huffmanCode[i] != NULL) {
            printf("%c: %s\n", (char) (i), huffmanCode[i]);
        }
    }

    printf("\nOriginal string was :\n%s\n", string);

    printf("\nEncoded string is :\n");
    char* encoded = (char*)(malloc(sizeof (char) * 1000000));
    for (int i = 0; i < strlen(string); ++i) {
        strcat(encoded, huffmanCode[(int)(string[i])]);
        printf("%s", huffmanCode[(int)(string[i])]);
    }

    int index = -1;
    printf("\nDecoded string is :\n");
    while (index < (int) (strlen(encoded)) - 1) {
        decode(root, &index, encoded);
    }
    free(encoded);
    free(frequency);
    deallocateQueue(pq);
}
