/*
 ****** 	Module for Video 	******
 */

#ifndef VIDEOMODULE_H
#define VIDEOMODULE_H

#include <stdint.h>

typedef struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} Color;

/*
        Functions that use other functions from the VideoDriver
*/
void clearScreen();
void deleteChar();
void drawCircle(Color color, int radio, int x, int y);
void drawRectangle(Color color, int x, int y, int b, int h);
void getSize(int* x, int* y);
void getCursor(int* x, int* y);
void setCursor(int x, int y);
void drawChar(char c, int x, int y, Color color);
void eraseScreen(int x1, int y1, int x2, int y2);

#endif
