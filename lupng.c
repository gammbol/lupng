#include "lupng.h"

int isHeader(unsigned char* header) {
  for (int i = 0; i < HEADER_LEN; i++) {
    if (header[i] != headerTemplate[i])
      return 0;
  }
  return 1;
}

int readChunk(lupng_chunk *chunk, FILE *file) {
  // reading chunk length first
  if (fread(&(chunk->length), sizeof(uint32_t), 1, file) == -1) {
    perror("LUPng: ");
    return -1;
  }

  // deserializing data
  chunk->length = btol8(chunk->length);

  // Chunk length field
  ssize_t cdSize = chunk->length * sizeof(uint8_t);
  // chunkSize = chunkType + chunkData + crc
  ssize_t chunkSize = sizeof(uint32_t) * 2 + cdSize;

  if (chunk->length != 0) {
    chunk->data = malloc(cdSize);
  }

  // reading the rest of the chunk
  // if (fread(chunk + sizeof(uint32_t), chunkSize, 1, file) == -1) {
  //   perror("LUPng: ");
  //   return -1;
  // }

  if (fread(chunk->type, sizeof(uint8_t), 4, file) == -1) {
    perror("LUPng: ");
    return -1;
  }

  if (fread(chunk->data, sizeof(uint8_t), chunk->length, file) == -1) {
    perror("LUPng: ");
    return -1;
  }

  if (fread(&chunk->crc, sizeof(uint32_t), 1, file) == -1) {
    perror("LUPng: ");
    return -1;
  }

  return 0;
}  

void printChunk(const lupng_chunk chunk) {
  printf("Length: %u\n", chunk.length);
  printf("Type: ");
  for(int i = 0; i < 4; i++) {
    printf("%02x ", chunk.type[i]);
  }
  printf("\n");
  for (int i = 0; i < chunk.length; i++) {
      printf("%02x ", chunk.data[i]);
      if ((i+1) % 20 == 0) printf("\n");
  }
  printf("\nCRC: %u\n", chunk.crc);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: lupng filename\n");
    return -1;
  }
  
  FILE *file = fopen(argv[1], "rb");
  if (!file) {
    perror("LUpng: ");
    return -1;
  }

  if (fread(header, HEADER_LEN, 1, file) == -1) {
    perror("LUpng: ");
    fclose(file);
    return -1;
  }

  if (!isHeader(header)) {
    fprintf(stderr, "LUPng: Wrong file format\n");
    fclose(file);
    return -1;
  }

  lupng_chunk chunk = {};
  if (readChunk(&chunk, file) == -1) {
    fprintf(stderr, "LUpng: Error while reading a chunk\n");
    fclose(file);
    return -1;
  }

  printChunk(chunk);

  fclose(file);
  return 0;
}
