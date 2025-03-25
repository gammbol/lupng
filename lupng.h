#ifndef LUPNG_H
#define LUPNG_H

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// header
// 89  50  4e  47  0d  0a  1a  0a
#define HEADER_LEN 8

static const unsigned char headerTemplate[HEADER_LEN] = 
    { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };

unsigned char header[HEADER_LEN];

int isHeader(unsigned char* header);

#endif