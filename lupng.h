#ifndef LUPNG_H
#define LUPNG_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    uint32_t chunkType;
    uint8_t *chunkData;
    uint32_t crc;
} lupng_chunk;

// Chunk Types
enum Chunks {
    IHDR,       // Image Header
    PLTE,       // Palette
    IDAT,       // Image Data
    IEND        // Image Trailer
};

// Checking data for being a PNG header
int isHeader(unsigned char* header);

#endif