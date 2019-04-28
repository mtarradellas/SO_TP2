#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

// Transformes a decimal to string. used for displaying the registers
char * decToStr(int num, char * buffer);

char *cpuVendor(char *result);

#endif