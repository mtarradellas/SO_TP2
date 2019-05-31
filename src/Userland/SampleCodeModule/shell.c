#include "include/shell.h"
#include <stdint.h>
#include "include/memoryModule.h"
#include "include/mutexModule.h"
#include "include/pongModule.h"
#include "include/processModule.h"
#include "include/prodCon.h"
#include "include/soundModule.h"
#include "include/stdlib.h"
#include "include/timeModule.h"
#include "include/videoModule.h"
#include "include/philosophers.h"
typedef enum {
  INVCOM,
  HELP,
  CLEAR,
  TIME,
  PONG,
  ZERODIV,
  INVOPCODE,
  LENIA,
  EXIT,
  PTEST,
  MEMTEST,
  PS,
  KILLTEST,
  STACKOV,
  MUTEX,
  PRODCON,
  PHILOSOPHERS
} Command;

#define MAXLEN 256

void _opCode();

typedef unsigned long int (*cmd)();

// Gets command ready to use in a switch function
static int getCommand(char* command);
// Checks if command is set to background or foreground
static void checkForeground(char* command);
// Executes the 'help' command. Displays help menu
static unsigned long int help();
// Executes the 'clear' command. Clears screen
static unsigned long int clear();
// Executes the 'time' command. Displays local time
static unsigned long int time();
// Executes the 'pong' command. Initializes the pong game
static unsigned long int pong();
// Executes the 'zerodiv' command. Triggers a Zero Division Exception
static unsigned long int zeroDiv();
// Executes the 'invopcode' command. Triggers an Invalid OP Code Exception
static unsigned long int invOpCode();
// Triggers a stack overflow by calling an endless recursive function
static unsigned long int stackOv();
// Executes the 'lenia' command. Makes beep sound
static unsigned long int lenia();
// Executes the 'exit' command. Exits the kernel
static unsigned long int exit();
// Displays the message for when a command was not recognized
static unsigned long int invCom();
// Displays table with processes information
static unsigned long int ps();
// Launches ProdCon application
static unsigned long int prodCon();
// Memory allocation test
static unsigned long int memTest();
// Multiple processes test wrapper
static unsigned long int pTestWrapper();
// Kills all processes from test
static unsigned long int killTest();
// Launches eating philosophers application
static unsigned long int philosophers();

static unsigned long int mutex();
static void pTest();
static void test1();
static void test2();

cmd command_array[] = {
    (cmd)invCom,   (cmd)help,         (cmd)clear,     (cmd)time,
    (cmd)pong,     (cmd)zeroDiv,      (cmd)invOpCode, (cmd)lenia,
    (cmd)exit,     (cmd)pTestWrapper, (cmd)memTest,   (cmd)ps,
    (cmd)killTest, (cmd)stackOv,      (cmd)mutex,     (cmd)prodCon,
    (cmd)philosophers};

int sonsVec[50];
int sonsSize = 0;
static int on;
static int foreground;
void initShell() {
  on = 1;
  printf(
      "\n~~WELCOME TO LENIA'S SHELL~~\n\nPlease type 'help' to find out about "
      "our commands\n\n\n");
  char command[MAXLEN];
  while (on) {
    foreground = 1;
    printf("\n$> ");
    clearBuffer(command);
    scanAndPrint(command);
    int com = getCommand(command);

    int pid = command_array[com]();
    if (pid == 0) {
      foreground = 0;
    }
    if (foreground == 1) {
      waitpid(pid);
    }
  }
  printf("\n\n End of program");
}

static int getCommand(char* command) {
  checkForeground(command);
  if (!strCmp("help", command)) return HELP;
  if (!strCmp("clear", command)) return CLEAR;
  if (!strCmp("time", command)) return TIME;
  if (!strCmp("pong", command)) return PONG;
  if (!strCmp("zerodiv", command)) return ZERODIV;
  if (!strCmp("invopcode", command)) return INVOPCODE;
  if (!strCmp("stackov", command)) return STACKOV;
  if (!strCmp("lenia", command)) return LENIA;
  if (!strCmp("exit", command)) return EXIT;
  if (!strCmp("ptest", command)) return PTEST;
  if (!strCmp("killtest", command)) return KILLTEST;
  if (!strCmp("memtest", command)) return MEMTEST;
  if (!strCmp("ps", command)) return PS;
  if (!strCmp("mutex", command)) return MUTEX;
  if (!strCmp("prodcon", command)) return PRODCON;
  if(!strCmp("philosophers", command)) return PHILOSOPHERS;
  return INVCOM;
}

static void checkForeground(char* command) {
  int len = strLen(command);
  if (len < 3) return;
  if (strCmp(" &", command + len - 2) == 0) {
    foreground = 0;
    command[len - 2] = 0;
    command[len - 1] = 0;
  }
}

static unsigned long int help() {
  printf("\n\n********  Help Menu  ********\n\n");
  printf("  * clear        :       Clears screen\n");
  printf("  * invopcode    :       Executes Invalid OP Code Interruption\n");
  printf("  * zerodiv      :       Executes Zero Division Interruption\n");
  printf("  * stackov      :       Executes Stack Overflow Exception via recursive function\n");
  printf("  * exit         :       Exits shell\n");
  printf("  * lenia        :       Beep\n");
  printf("  * time         :       Displays current time\n");
  printf("  * prodcon      :       Launches ProdCon application\n");
  printf("  * memtest      :       Shows functioning Memory Management\n");
  printf("  * ptest        :       Runs multiple processes to show functionality\n");
  printf("  * killtest     :       Kills all processes created from ptest command\n");
  printf("  * mutex        :       Runs the mutex test\n");
  printf("  * philosophers :       Runs the eating philosophers application\n");
  printf("  * ps           :       Displays process table with, name, pid, status, foreground, memory, priority\n");
  printf("  * pong         :       Iniciates pong when user presses 'enter' which will run until\n");
  printf("                         end of game or until user presses 'backspace' to leave\n");
  printf("\n  Any other command will be taken as invalid\n");
  printf("Commands may be executed on background by typing ' &' at the end\n");
  return 0;
}

static unsigned long int clear() {
  clearScreen();
  printf("\n~~Welcome to Lenia's Shell~~\n\n");
  return 0;
}

static unsigned long int time() {
  unsigned int h = getHour();
  unsigned int m = getMinute();
  unsigned int s = getSecond();
  printf("\nLocal Time: %d:%d:%d", h, m, s);
  return 0;
}

static unsigned long int pong() {
  startPong();
  clear();
  return 0;
}

static unsigned long int zeroDiv() {
  int a = 0;
  a = 2 / a;
  return 0;
}

static unsigned long int invOpCode() {
  _opCode();
  return 0;
}

static unsigned long int stackOv() {
  printf(
      "\n        "
      "////////////////////////////////////////////////////////////////////////"
      "////////////////////////////////////\n");
  printf(
      "        //////////////////////////////////////////  ///////  "
      "///////////////////////////////////////////////////////\n");
  printf(
      "        //////////////////////////////////////////  ///////  "
      "///////////////////////////////////////////////////////\n");
  printf(
      "        "
      "////////////////////////////////////////////////////////////////////////"
      "////////////////////////////////////\n");
  printf(
      "        /////////////////////////////////////////              "
      "//////////////////////////////////////////////////////\n");
  printf(
      "        ///////////////////////////////////////  /////////////  "
      "////////////////////////////////////////////////////\n");
  printf(
      "        "
      "////////////////////////////////////////////////////////////////////////"
      "////////////////////////////////////\n");
  stackOv();
  return 0;
}

static unsigned long int lenia() {
  doBeep();
  wait(20);
  noBeep();
  return 0;
}

static unsigned long int exit() {
  on = 0;
  return 0;
}

static unsigned long int invCom() {
  printf("\nInvalid command");
  return 0;
}

static unsigned long int ps() {
  tProcessData** psVec;
  int size;
  getPS(&psVec, &size);

  printf("\nPID     Status     Memory    Priority     Name\n");
  for (int i = 0; i < size; i++) {
    printf("%d       %s    %d      %s      %s\n", psVec[i]->pid,
           psVec[i]->status, psVec[i]->memory, psVec[i]->priority,
           psVec[i]->name);
    free(psVec[i]->name);
    free(psVec[i]);
  }
  free(psVec);
  return 0;
}

static unsigned long int prodCon() {
  //return createProcess("ProdCon", (mainf)startProdCon, 0, NULL, HIGHP);
  startProdCon();
  return 0;
}

static unsigned long int philosophers() {
  philosophersRun();
  return 0;
}
static unsigned long int memTest() {
  char* mem = malloc(25);
  printf(
      "\n Memory has been allocated correctly (and string has been inserted). "
      "Showing memory block:");

  char copy[25] = "Penguins have knees";
  memcpy(mem, copy, sizeof(copy));

  printNode(mem);

  free(mem);
  printf("Memory has been freed. Showing memory block:\n");

  printNode(mem);

  char* mem2 = malloc(16);
  printf(
      "\n New memory has been allocated correctly in the same block. Showing "
      "memory block:");

  printNode(mem2);
  char copy2[16] = "it works, relax";
  memcpy(mem, copy2, sizeof(copy2));

  printf("\n Showing memory block with new inserted string:");
  printNode(mem2);

  free(mem2);
  printf("Memory has been freed.\n");

  printf(
      "\n        "
      "////////////////////////////////////////////////////////////////////////"
      "////////////////////////////////////\n");
  printf(
      "        //////////////////////////////////////////  ///////  "
      "///////////////////////////////////////////////////////\n");
  printf(
      "        //////////////////////////////////////////  ///////  "
      "///////////////////////////////////////////////////////\n");
  printf(
      "        "
      "////////////////////////////////////////////////////////////////////////"
      "////////////////////////////////////\n");
  printf(
      "        ///////////////////////////////////////  ////////////  "
      "/////////////////////////////////////////////////////\n");
  printf(
      "        ////////////////////////////////////////             "
      "///////////////////////////////////////////////////////\n");
  printf(
      "        "
      "////////////////////////////////////////////////////////////////////////"
      "////////////////////////////////////\n");
  return 0;
}

static unsigned long int pTestWrapper() {
  return createProcess("procWrapp", (mainf)pTest, 0, NULL, MIDP);
}

int global = 0;


static void doSomething() {
  mutexLock("pepe");
  global += 1;
  printf("\n Job %d started\n", global);
  wait(15);
  ps();
  printf("\n Job %d finished\n", global);
  mutexUnlock("pepe");
}

static unsigned long int mutex() {
  int amount = 3;
  mutexOpen("pepe");
  global = 0;
  char** argv = NULL;
  int procs[amount];
  for (int i = 0; i < amount; i++) {
    procs[i] = createProcess("mutexTest", (mainf)doSomething, 0, argv, HIGHP);
  }

  for (int i = 0; i < amount; i++) {
    waitpid(procs[i]);
  }

  mutexClose("pepe");
  return 0;
}

static void pTest() {
  if (sonsSize > 48) {
    printf(
        "Maximun processes created, please wait for some to end or kill all "
        "with 'killtest' command\n");
    return;
  }
  printf("\nCreating two processes that will end after a couple of seconds\n");
  printf("Process 1 has high priority, process 2 has low priority\n");

  printf(
      "If on background, you may kill all test processes at anytime with "
      "'killtest' command\n");
  int pid1 = createProcess("test1", (mainf)test1, 0, NULL, HIGHP);
  int pid2 = createProcess("test2", (mainf)test2, 0, NULL, LOWP);
  sonsVec[sonsSize++] = pid1;
  sonsVec[sonsSize++] = pid2;
  waitpid(pid1);
  waitpid(pid2);
  printf("\n");
}

static unsigned long int killTest() {
  for (int i = 0; i < sonsSize; i++) {
    kill(sonsVec[i]);
  }
  sonsSize = 0;
  return 0;
}

static void test1() {
  int i = 0;
  while (i < 7) {
    printf("  1  ");
    wait(30);
    i++;
  }
  printf(" test 1 done ");
  return;
}

static void test2() {
  int i = 0;
  while (i < 7) {
    printf("  2  ");
    wait(30);
    i++;
  }
  printf(" test 2 done ");
}