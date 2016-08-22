#ifndef UI_HELPER_H
#define UI_HELPER_H

typedef enum {
	NORMAL,
	INVERSE
} clear_line;


void clearWindow (int line, clear_line how, int window);
void clearScreen(int nation, char *topleft, char *bottomleft, char *bottomright);
void initCurses(void);
void printCenter(int starty, int startx, int width, char *string);
void printRightBottom(int nation, int startx, int width, char *string, int year);

void printCenterH(int starty, int startx, int width, char *string, int highlighted);
int drawmenu(int items, int size, int highlighted, char test[items][size]);
void HighlightLine (int line, clear_line how);
int drawcustommenu(int items, int size, int highlighted, char test[items][size], int interval, int yoffset, int xoffset);
#endif
