#ifndef HUFFMAN_COMPRESION_H
#define HUFFMAN_COMPRESION_H

typedef struct huffman_encoding* HUFFMAN_ENCODING;

HUFFMAN_ENCODING initialize_huffman_encoding();
int is_character_in_huffman_enconding(HUFFMAN_ENCODING, const char character);
void add_character_to_huffman_encoding(HUFFMAN_ENCODING, const char character, const unsigned frequency);
void create_encoding(HUFFMAN_ENCODING);
void get_encoding_for_char(HUFFMAN_ENCODING, const char character, char *where_to_store);
void dealloc_huffman_encoding(HUFFMAN_ENCODING);

#endif /* HUFFMAN_COMPRESION_H */