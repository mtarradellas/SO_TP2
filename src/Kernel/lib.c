#include <stdint.h>

#define A 25214903917
#define C 11
#define M 281474976710656

#define MOD 50

void *memset(void *destination, int32_t c, uint64_t length) {
  uint8_t chr = (uint8_t)c;
  char *dst = (char *)destination;

  while (length--) dst[length] = chr;

  return destination;
}


void *memcpy(void *destination, const void *source, uint64_t length) {
  /*
   * memcpy does not support overlapping buffers, so always do it
   * forwards. (Don't change this without adjusting memmove.)
   *
   * For speedy copying, optimize the common case where both pointers
   * and the length are word-aligned, and copy word-at-a-time instead
   * of byte-at-a-time. Otherwise, copy by bytes.
   *
   * The alignment logic below should be portable. We rely on
   * the compiler to be reasonably intelligent about optimizing
   * the divides and modulos out. Fortunately, it is.
   */
  uint64_t i;

  if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
      (uint64_t)source % sizeof(uint32_t) == 0 &&
      length % sizeof(uint32_t) == 0) {
    uint32_t *d = (uint32_t *)destination;
    const uint32_t *s = (const uint32_t *)source;

    for (i = 0; i < length / sizeof(uint32_t); i++) d[i] = s[i];
  } else {
    uint8_t *d = (uint8_t *)destination;
    const uint8_t *s = (const uint8_t *)source;

    for (i = 0; i < length; i++) d[i] = s[i];
  }

  return destination;
}

char *decToStr(int num, char *buffer) {
  char const digit[] = "0123456789";
  char *p = buffer;
  if (num < 0) {
    *p++ = '-';
    num *= -1;
  }
  int shifter = num;
  do {  // Move to where representation ends
    ++p;
    shifter = shifter / 10;
  } while (shifter);
  *p = '\0';
  do {  // Move back, inserting digits as you go
    *--p = digit[num % 10];
    num = num / 10;
  } while (num);
  return buffer;
}

unsigned long int var = 1;

void srand(unsigned long int seed) { var = seed; }

void lcg(unsigned long int *x, unsigned long int a, int c,
         unsigned long int m) {
  *x = (a * (*x) + c) % m;
}

unsigned long int rand() {
  lcg(&var, A, C, M);
  return var;
}

int strcmp(char* a, char* b) {
  while (*a && *b) {
    if (*a > *b) return 1;
    if (*a < *b) return -1;
    a++;
    b++;
  }
  if (*a) return 1;
  if (*b) return -1;
  return 0;
}

int strlen(char* str) {
  int len = 0;
  while(*str != 0) {
    len++;
    str++;
  }
  return len;
}
/*
#include <stdio.h>
#include <stdint.h>

void srand(unsigned long int seed);
void lcg(unsigned long int *x, unsigned long int a, int c, unsigned long int m);
unsigned long int lcgParkMiller(unsigned long int *x);
unsigned long int mylcg(unsigned long int *x);
unsigned long int rand();
unsigned long int rand2();

unsigned long int myVar = 1;
unsigned long int parlMillerVar = 7;

void srand(unsigned long int seed) {
  myVar = seed;
}

void lcg(unsigned long int *x, unsigned long int a, int c, unsigned long int m) {
  *x = (a*(*x)+c) % m;
}

unsigned long int lcgParkMiller(unsigned long int *x) {
  lcg(x, 48271, 0, 2147483647);
  return *x;

}

unsigned long int mylcg(unsigned long int *x) {
  lcg(x, 25214903917, 11, 281474976710656);
  return *x;
}

unsigned long int rand() {
  return mylcg(&myVar);
}

unsigned long int PMrand() {
    return lcgParkMiller(&parlMillerVar);
}

int main() {
  int vec1[10] = {0};
  int vec2[10] = {0};
  int a, b;

  printf("My lcg:\n");
  for (int i = 0; i < 500; i++) {
    a = rand() % 10;
    //printf("%d | ", a);
    vec1[a]++;

  }
  printf("\nParker-Miller:\n");
  for (int i = 0; i < 500; i++) {
    b = rand2() % 10;
    //printf("%d | ", b);
    vec2[b]++;
  }
  printf("\nVec 1:  Vec 2:\n");
  for (int i = 0; i < 10; i++) {
    printf("%d:  %d       %d\n", i, vec1[i], vec2[i]);
  }
  return 0;
}
*/