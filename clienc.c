#include <stdio.h>
#include "huffman_compresion.h"

int main() {
    HUFFMAN_ENCODING huffman_encoding = initialize_huffman_encoding();
    add_character_to_huffman_encoding(huffman_encoding, 'A', 10);
    add_character_to_huffman_encoding(huffman_encoding, 'D', 2);
    add_character_to_huffman_encoding(huffman_encoding, 'E', 5);
    add_character_to_huffman_encoding(huffman_encoding, 'Z', 1);

    create_encoding(huffman_encoding);
    dealloc_huffman_encoding(huffman_encoding);

    return 0;
}