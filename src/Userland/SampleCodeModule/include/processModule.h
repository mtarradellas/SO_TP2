#ifndef PROCESSMODULE_H
#define PROCESSMODULE_H

#define HIGHP 250
#define MIDP 150
#define LOWP 10

typedef struct tProcessData {
  unsigned long int pid;
  char* name;
  char* status;
  int memory;
  char* priority;
} tProcessData;

unsigned long int createProcess(char* name, int (*entry)(int, char**), int argc, char** argv, int priority);
void kill(unsigned long int);
void getPS(tProcessData*** psVec, int *size);

#endif