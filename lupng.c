#include "lupng.h"

int isHeader(unsigned char* header) {
  for (int i = 0; i < HEADER_LEN; i++) {
    if (header[i] != headerTemplate[i])
      return 0;
  }
  printf("got here\n");
  return 1;
}

int readChunck(lupng_chunk *chunk, FILE *file) {
  // reading chunk length first
  if (fread(&chunk->length, sizeof(uint32_t), 1, file) == -1) {
    perror("LUPng: ");
    return -1;
  }

  // Chunk length field
  ssize_t cdSize = chunk->length * sizeof(uint8_t);
  // chunkSize = chunkType + chunkData + crc
  ssize_t chunkSize = sizeof(uint32_t) * 2 + cdSize;

  if (chunk->chunkLength != 0) {
    chunk->chunkData = malloc(cdSize);
  }

  // reading the rest of the chunk
  if (fread(chunk + sizeof(uint32_t), chunkSize, 1, file) == -1) {
    perror("LUPng: ");
    return -1;
  }

  return 0;
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

  for (int i = 0; i < 8; i++) {
    printf("%02x ", header[i]);
  }
  printf("\n");

  for (int i = 0; i < 8; i++) {
    printf("%02x ", headerTemplate[i]);
  }
  printf("\n");

  if (!isHeader(header)) {
    fprintf(stderr, "LUPng: Wrong file format\n");
    fclose(file);
    return -1;
  }

  fclose(file);
  return 0;
}
