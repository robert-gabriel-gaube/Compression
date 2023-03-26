#include "huffman_compresion.h"
#include "priority_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_CHARACTERS 26

typedef struct{
    unsigned frequency;
    char encoding[10];
}HUFFMAN_CHARACTER;

priority_queue(HUFFMAN_CHARACTER);

struct huffman_encoding {
    HUFFMAN_CHARACTER characters[NUMBER_CHARACTERS];
};

void throw_error(const char* msg) {
    printf("ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

unsigned character_position(const char character) {
    if(character == ' ') return NUMBER_CHARACTERS - 1;
    else if(character >= 'A' && character <= 'Z') return character - 'A';
    else throw_error("Character not recognized");   
    return 0;
}

HUFFMAN_ENCODING initialize_huffman_encoding() {
    HUFFMAN_ENCODING huffman_encoding = (HUFFMAN_ENCODING)malloc(sizeof(struct huffman_encoding));
    if(huffman_encoding == NULL) {
        throw_error("Not enough space available");
    }
    for(unsigned i = 0; i < NUMBER_CHARACTERS; ++i) {
        huffman_encoding->characters[i].frequency = 0;
        strcpy(huffman_encoding->characters[i].encoding, "");
    }
    return huffman_encoding;
}

int is_character_in_huffman_enconding(HUFFMAN_ENCODING huffman_encoding, const char character) {
    unsigned char_position = character_position(character);
    return huffman_encoding->characters[char_position].frequency != 0;
}
void add_character_to_huffman_encoding(HUFFMAN_ENCODING huffman_encoding, const char character, const unsigned frequency) {
    unsigned char_position = character_position(character);
    if(huffman_encoding->characters[char_position].frequency != 0) {
        throw_error("Character already added");
    }
    huffman_encoding->characters[char_position].frequency = frequency;
}
void create_encoding(HUFFMAN_ENCODING huffman_encoding) {

}