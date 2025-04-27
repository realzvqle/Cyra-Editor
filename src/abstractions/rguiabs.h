#ifndef RGUIABS_H_INCLUDED
#define RGUIABS_H_INCLUDED






#include "../cyra.h"




void RGUIInit();
Color RGUIGetApplicationColor();
int RGUIDrawButton(int x, int y, int width, int height, const char* text);
void RGUIDrawText(char* text, int x, int y, int fontsize, Color tint);
Font RGUIGetFont();
int RGUIDrawWindow(int x, int y, int width, int height, char* title);
int RGUIDrawTextBox(int x, int y, int width, int height, char* text, int textlim);
#endif