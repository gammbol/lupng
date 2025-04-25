#ifndef LUPNG_H
#define LUPNG_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <seria.h>

// header
// 89  50  4e  47  0d  0a  1a  0a
#define HEADER_LEN 8

// PNG header template
static const unsigned char headerTemplate[HEADER_LEN] = 
    { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };

// PNG header
unsigned char header[HEADER_LEN];

// Chunk structure
typedef struct {
    uint32_t length;
    uint8_t type[4];
    uint8_t *data;
    uint32_t crc;
} lupng_chunk;

// Chunk Types
enum Chunks {
    IHDR,       // Image Header
    PLTE,       // Palette
    IDAT,       // Image Data
    IEND        // Image Trailer
};

// 0 - not header
// 1 - header
// checking if array is a png file header
int isHeader(unsigned char* header);


// -1 - error
// 0 - success
// reading a chunk of png file
int readChunk(lupng_chunk *chunk, FILE *file); 

// debug
void printChunk(const lupng_chunk chunk);

#endif
