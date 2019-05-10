#ifndef IPC_MUTEX_H
#define IPC_MUTEX_H
#include <stddef.h>
#include "./PIDQueue.h"
typedef struct {
  int value;
  unsigned long ownerPID;
  PIDQueue lockedQueue;
} tMutex;

typedef tMutex* mutex_t;
mutex_t mutexCreate();
void mutexDelete(mutex_t mutex);
void mutexLock(mutex_t mutex);
void mutexUnlock(mutex_t mutex);

#endif