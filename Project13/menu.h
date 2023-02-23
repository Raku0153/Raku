#ifndef _MENU_H

#define _MENU_H
void mainMenu(int x, int y);
void mapMenu(int x, int y);
void title(int x, int y, int choice);
int menuControl(int keyData, int* x, int* y);
int menuChoice();
int mapChoice();
void how();

#endif