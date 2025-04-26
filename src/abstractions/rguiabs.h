#ifndef RGUIABS_H_INCLUDED
#define RGUIABS_H_INCLUDED






#include "../editor.h"




void RGUIInit();
int RGUICreateButton(int x, int y, int width, int height, const char* text);
void RGUIDrawText(char* text, int x, int y, int fontsize, Color tint);
int RGUICreateMainTextBox(int x, int y, int width, int height, char* text, int* currentIndex, int fontSize, int textLimit);

#endif