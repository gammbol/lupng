#include "lupng.h"

int isHeader(unsigned char* header) {
  for (int i = 0; i < HEADER_LEN; i++) {
    if (header[i] != headerTemplate[i])
      return 0;
  }
  printf("got here\n");
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: lupng filename\n");
    return -1;
  }
  
  FILE *file = fopen(argv[1], "rb");
  if (!file) {
    perror("LUpng file error: ");
    return -1;
  }

  if (fread(header, HEADER_LEN, 1, file) == -1) {
    perror("LUpng read error: ");
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
    fprintf(stderr, "LUPng file error: wrong file format\n");
    fclose(file);
    return -1;
  }

  fclose(file);
  return 0;
}
