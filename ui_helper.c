#include "ui_helper.h"
#include <ncurses.h>
#include <string.h>
#include "space.h"
#include "menus.h"
extern struct hardware rocket[];
extern struct hardware unmanned[];
extern struct hardware capsule[];
extern struct hardware misc[];

// this function clears the screen and redraws basic game interface
void clearScreen (int nation, char *topleft, char *bottomleft, char *bottomright)
{
	// clear the screen by erase rather than clear = no flicker
	werase(top_win);
	werase(middle_win);
	werase(bottom_win);

	if (nation == 2 || nation == 3)  // have we started a game yet?
	{
		wattron(top_win,COLOR_PAIR(nation));   // set UI color and such depending on
		wattron(bottom_win,COLOR_PAIR(nation));// nation of current player
		wattron(top_win,WA_REVERSE);
		wattron(bottom_win,WA_REVERSE);
		clearWindow (0, NORMAL, 1);
		clearWindow (0, NORMAL, 3);
		mvwprintw(top_win,0,1,"%s", topleft);
		switch(nation)
		{
			case 2:
				mvwprintw(top_win,0,COLS-7,"U.S.A.");
				break;
			case 3:
				mvwprintw(top_win,0,COLS-9,"U.S.S.R.");
				break;
		}
		mvwprintw(bottom_win,0,1, "Current Budget: %d MB  |  Cash: %d MB", currentplayer->currentbudget, currentplayer->cash);
		switch(currentgame.season)
		{
			case 1:
				printRightBottom(currentplayer->nation,0,0, "Spring ", currentgame.year);
				break;
			case 2:
				printRightBottom(currentplayer->nation,0,0, "Fall ", currentgame.year);
				break;
		}
		wattroff(top_win,COLOR_PAIR(nation));
		wattroff(bottom_win,COLOR_PAIR(nation));
		wattroff(top_win,WA_REVERSE);
		wattroff(bottom_win,WA_REVERSE);

	}
	else  // or we haven't started a game, so draw in white
	{
		wattron(bottom_win,COLOR_PAIR(1));
		wattron(top_win,COLOR_PAIR(1));
		wattron(top_win,WA_REVERSE);
		wattron(bottom_win,WA_REVERSE);
		clearWindow (0, NORMAL, 1);
		clearWindow (0, NORMAL, 3);
		mvwprintw(top_win,0,1,"%s", topleft);
		mvwprintw(bottom_win,0,1, "%s", bottomleft);
		wattroff(bottom_win,WA_REVERSE);
		wattroff(bottom_win,COLOR_PAIR(1));
		wattroff(top_win,WA_REVERSE);
		wattroff(top_win,COLOR_PAIR(1));


	}
	wrefresh(top_win);
	wrefresh(middle_win);
	wrefresh(bottom_win);
}

//this function draws a colored bar at the top or bottom of the screen
void clearWindow (int line, clear_line how, int window)
{
	int i;

	if (how == INVERSE)
		attron(WA_REVERSE);

	if (window == 1)
	{
		for (i = 0; i < COLS; i++)
		{
			mvwaddch (top_win,line, i, ' ');
		}
	}
	else
	{
		for (i = 0; i < COLS; i++)
		{
			mvwaddch (bottom_win,line, i, ' ');
		}
	}
	if (how == INVERSE)
		attroff(WA_REVERSE);
}

// starting curses stuff all in one function
void initCurses (void)
{
	initscr();					/* Start curses mode */
	cbreak();					/* Line buffering disabled, Pass on everything to me */
	keypad(stdscr, TRUE);		/* I need that nifty F1 */
	noecho();					/* Do not echo typed chars to screen */
	start_color();				/* Start color */
	curs_set(0);				/* Hide the cursor */
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	refresh();
}

// function to print stuff centered in the middle window
void printCenter(int starty, int startx, int width, char *string)
{
	int length, x, y;
	float temp;
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;
	width = COLS;
	length = strlen(string);
	temp = (width - length)/ 2;
	x = (int)temp;
	//attron(COLOR_PAIR(1));
	wattron(middle_win,COLOR_PAIR(1));
	mvwprintw(middle_win, y, x, "%s", string);
	//attroff(COLOR_PAIR(1));
	wattroff(middle_win,COLOR_PAIR(1));
	wrefresh(middle_win);
}

// prints stuf in the bottom right of the screen, namely season and year
void printRightBottom(int nation, int startx, int width, char *string, int year)
{
	int length, x, y;
	float temp;
	if(startx != 0)
		x = startx;
	if(width == 0)
		width = 80;

	x = COLS;
	y = LINES;
	length = (strlen(string)) + 5;
	temp = x - length;
	x = (int)temp;
	//attron(COLOR_PAIR(nation));
	mvwprintw(bottom_win, 0, x, "%s", string);
	temp = x + strlen(string);
	x = (int)temp;
	mvwprintw(bottom_win, 0, x, "%d", year);
	//attroff(COLOR_PAIR(nation));
	wrefresh(bottom_win);
}


// print stuff centered in the middle window and highlight one line, useful for menus
void printCenterH(int starty, int startx, int width, char *string, int highlighted)
{
	int length, x, y;
	float temp;
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;
	width = COLS;
	length = strlen(string);
	temp = (width - length)/ 2;
	x = (int)temp + startx;
	//attron(COLOR_PAIR(1));
	//
	if (starty == highlighted)
	{
		wattron(middle_win,COLOR_PAIR(1));
		wattron(middle_win,WA_REVERSE);
		HighlightLine(starty,NORMAL);
		mvwprintw(middle_win, y, x, "%s", string);
		//attroff(COLOR_PAIR(1));
		wattroff(middle_win,WA_REVERSE);
		wattroff(middle_win,COLOR_PAIR(1));
		wrefresh(middle_win);

	}
	else
	{
		wattron(middle_win,COLOR_PAIR(1));
		mvwprintw(middle_win, y, x, "%s", string);
		//attroff(COLOR_PAIR(1));
		wattroff(middle_win,COLOR_PAIR(1));
		wrefresh(middle_win);
	}

}


// draws a menu from an array, knows how to deal with user interaction
// and uses the printCenterH function to highlight selected entry
int drawmenu(int items, int size, int highlighted, char test[items][size])
{
	int ch = 0;
	while (ch < items)
	{
		printCenterH(ch,0,0, test[ch], highlighted);
		ch++;
	}
	while (ch = getch())
	{
		switch(ch)
		{
			case KEY_UP:
				if (highlighted == 1)
				{
					highlighted = items-1;
				}
				else
				{
					highlighted--;
				}
				werase(middle_win);
				ch = 0;
				while (ch < items)
				{
					printCenterH(ch,0,0, test[ch], highlighted);
					ch++;
				}
				break;
			case KEY_DOWN:
				if (highlighted == items-1)
				{
					highlighted = 1;
				}
				else
				{
					highlighted++;
				}
				ch = 0;
				werase(middle_win);
				while (ch < items)
				{
					printCenterH(ch,0,0, test[ch], highlighted);
					ch++;
				}
				break;
			case '\n':
				return highlighted;
				break;

		}

	}

}

// highlight a line, called by printCenterH amongst others
void HighlightLine (int line, clear_line how) {
	int i;

	if (how == INVERSE)
		wattron(middle_win,WA_REVERSE);

	for (i = 0; i < COLS; i++) {
		mvwaddch (middle_win,line, i, ' ');
	}



	if (how == INVERSE)
		wattroff(middle_win,WA_REVERSE);
}



// used to draw a menu where specific placement is need
int drawcustommenu(int items, int size, int highlighted, char test[items][size], int interval, int yoffset, int xoffset)
{
	int ch = 0;
	int yoffsetb = yoffset;
	while (ch < items)
	{
		printCenterH(yoffset,xoffset,0, test[ch], highlighted);
		ch++;
		yoffset = yoffset+interval;
	}
	yoffset = yoffsetb;
	while (ch = getch())
	{
		switch(ch)
		{
			case KEY_UP:
				if (highlighted == yoffset)
				{
					highlighted = yoffset+interval*(items-1);
				}
				else
				{
					highlighted = highlighted -interval;
				}
				werase(middle_win);
				ch = 0;
				while (ch < items)
				{
					printCenterH(yoffset,xoffset,0, test[ch], highlighted);
					ch++;
					yoffset = yoffset+interval;
				}
				yoffset = yoffsetb;
				(*fptr)(highlighted);
				return 0;
				break;
			case KEY_DOWN:
				if (highlighted == yoffset+interval*(items-1))
				{
					highlighted = yoffset;
				}
				else
				{
					highlighted = highlighted + interval;
				}
				ch = 0;
				werase(middle_win);
				while (ch < items)
				{
					printCenterH(yoffset,xoffset,0, test[ch], highlighted);
					ch++;
					yoffset = yoffset+interval;
				}
				yoffset = yoffsetb;
				(*fptr)(highlighted);
				return 0;
				break;
			case '\n':
				return highlighted;
				break;

		}

	}

}


int drawmenun(int items, int size, int highlighted, char test[items][size])
{
	int ch = 0;
	while (ch < items)
	{
		printCenterH(ch,0,0, test[ch], highlighted);
		ch++;
	}
	while (ch = getch())
	{
		switch(ch)
		{
			case KEY_UP:
				if (highlighted == 1)
				{
					highlighted = items-1;
					//return highlighted;
				}
				else
				{
					highlighted--;
					//return highlighted;
				}
				werase(middle_win);
				ch = 0;
				while (ch < items)
				{
					printCenterH(ch,0,0, test[ch], highlighted);
					ch++;
				}
				return highlighted;
				break;
			case KEY_DOWN:
				if (highlighted == items-1)
				{
					highlighted = 1;
					//return highlighted;
				}
				else
				{
					highlighted++;
					//return highlighted;
				}
				ch = 0;
				werase(middle_win);
				while (ch < items)
				{
					printCenterH(ch,0,0, test[ch], highlighted);
					ch++;
				}
				return highlighted;
				break;
			case '\n':
				return -1;
				break;

		}

	}

}


int drawmenuc(int items, int size, int highlighted, char test[items][size])
{
	int ch = 0;
  /*  while (ch < items)
	{
		printCenterH(ch,0,0, test[ch], highlighted);
	ch++;
	}
	while (ch = getch())
	{
		switch(ch)
		{	 case KEY_UP:
		   if (highlighted == 1)
		   {
			   highlighted = items-1;
		   }
		   else
		   {
			   highlighted--;
		   }
		   werase(middle_win);
		   ch = 0;
		   (while (ch < items)
			   {
				  printCenterH(ch,0,0, test[ch], highlighted);
				  ch++;
			   }
		   break;
		 case KEY_DOWN:
		   if (highlighted == items-1)
		   {
			   highlighted = 1;
		   }
		   else
		   {
			   highlighted++;
		   }
		   ch = 0;
		   werase(middle_win);
		   while (ch < items)
			   {
				  printCenterH(ch,0,0, test[ch], highlighted);
				  ch++;
			   }
		   break;
		 case '\n':
		   return highlighted;
		   break;

		 }

	}*/

	draw_hardware_info();

	attron(COLOR_PAIR(1));

	mvprintw(3,COLS/2-1,"^^^");
	mvprintw(LINES-3,COLS/2-1,"vvv");
	mvprintw(LINES/2-1,COLS-2,">");
	mvprintw(LINES/2,COLS-2,">");
	mvprintw(LINES/2+1,COLS-2,">");
	mvprintw(LINES/2-1,0+2,"<");
	mvprintw(LINES/2,0+2,"<");
	mvprintw(LINES/2+1,0+2,"<");
	attroff(COLOR_PAIR(1));

	refresh();


	while ( ch = getch() )
	{

		int tid = currenthardware->tid;


		switch(ch)
		{
			case KEY_UP:
				if (currenthardware->category == 1)
					currenthardware = &unmanned[0];
				else if (currenthardware->category == 2)
					currenthardware = &misc[0];
				else if (currenthardware->category == 3)
					currenthardware = &rocket[0];
				else
					currenthardware = &capsule[0];
				break;
			case KEY_DOWN:
				if (currenthardware->category == 1)
					currenthardware = &capsule[0];
				else if (currenthardware->category == 2)
					currenthardware = &rocket[0];
				else if (currenthardware->category == 3)
					currenthardware = &misc[0];
				else
					currenthardware = &unmanned[0];
				break;
			case KEY_LEFT:
				if (currenthardware->tid != 0)
				{
					switch (currenthardware->category)
					{
						case 1:
							currenthardware = &rocket[tid-1];
							break;
						case 2:
							currenthardware = &unmanned[tid-1];
							break;
						case 3:
							currenthardware = &capsule[tid-1];
							break;
						case 4:
							currenthardware = &misc[tid-1];
							break;
					}


				}
				else
				{
					int tid = currenthardware->tid;
					switch (currenthardware->category)
					{
						case 1:
							currenthardware = &rocket[3];
							break;
						case 2:
							currenthardware = &unmanned[2];
							break;
						case 3:
							currenthardware = &capsule[6];
							break;
						case 4:
							currenthardware = &misc[3];
							break;
					}
				}
				break;
			case KEY_RIGHT:
				switch (currenthardware->category)
				{
					case 1:
						if (rocket[tid+1].tid == tid+1)
							currenthardware = &rocket[tid+1];
						else
							currenthardware = &rocket[0];
						break;
					case 2:
						if (unmanned[tid+1].tid == tid+1)
							currenthardware = &unmanned[tid+1];
						else
							currenthardware = &unmanned[0];
						break;
					case 3:
						if (capsule[tid+1].tid == tid+1)
							currenthardware = &capsule[tid+1];
						else
							currenthardware = &capsule[0];
						break;
					case 4:
						if (misc[tid+1].tid == tid+1)
							currenthardware = &misc[tid+1];
						else
							currenthardware = &misc[0];
						break;
				}

				break;
		}
		draw_hardware_info();
		attron(COLOR_PAIR(1));
		mvprintw(3,COLS/2-1,"^^^");
		mvprintw(LINES-3,COLS/2-1,"vvv");
		mvprintw(LINES/2-1,COLS-2,">");
		mvprintw(LINES/2,COLS-2,">");
		mvprintw(LINES/2+1,COLS-2,">");
		mvprintw(LINES/2-1,0+2,"<");
		mvprintw(LINES/2,0+2,"<");
		mvprintw(LINES/2+1,0+2,"<");
		attroff(COLOR_PAIR(1));
		refresh();

	}

}


int draw_hardware_info()
{
	clearScreen(currentplayer->nation,"","","");
	int ch;
	//printCenter(2,0,0,"Atlas Rocket");
	attron(COLOR_PAIR(currentplayer->nation));
	attron(WA_REVERSE);
	mvprintw(0,8,"Research & Development -> %s -> %s", currenthardware->type, currenthardware->name);
	attroff(COLOR_PAIR(currentplayer->nation));
	attroff(WA_REVERSE);


	attron(COLOR_PAIR(1));
	if (currenthardware->onhand == 0 && currenthardware->safety == 0)
	{
		attron(COLOR_PAIR(3));
		mvprintw(3,8,"No program initiated");
		attroff(COLOR_PAIR(3));
	}
	else
	{
		attron(COLOR_PAIR(4));
		mvprintw(3,8,"Units on hand: %d", currenthardware->onhand);
		attroff(COLOR_PAIR(4));
	}
	attron(COLOR_PAIR(1));
	mvprintw(4,8, "Inital cost: %d", currenthardware->cost);
	mvprintw(5,8, "Unit cost: %d", currenthardware->unit);
	if (currenthardware->safety > 75)
	{
		attron(COLOR_PAIR(4));
		mvprintw(6,8, "Safety factor: %d %", currenthardware->safety);
		attroff(COLOR_PAIR(4));
	}
	else
	{
		attron(COLOR_PAIR(3));
		mvprintw(6,8, "Safety factor: %d %", currenthardware->safety);
		attroff(COLOR_PAIR(3));
	}
	attron(COLOR_PAIR(1));
	mvprintw(7,8, "R&D cost per team: %d", currenthardware->rdcost);
	if (currenthardware->weight == 0)
	{
		mvprintw(8,8, "Unit weight: N/A");
	}
	else
	{
		mvprintw(8,8, "Unit weight: %d", currenthardware->weight);
	}
	if (currenthardware->payload == 0)
	{
		mvprintw(9,8, "Maximum payload: N/A");
	}
	else
	{
		mvprintw(9,8, "Maximum payload: %d", currenthardware->payload);
	}
	mvprintw(10,8, "Maximum R&D: %d %", currenthardware->rdmax);
	mvprintw(11,8, "Maximum safety: %d %", currenthardware->safetymax);
	/*printCenter(6,0,0,"Rockets");
	printCenter(7,0,0,"Capsules");
	printCenter(8,0,0,"Misc");*/
	printCenter(12,0,0,"(F1)Research 1, (F2) 2, (F3) 3, (F4) 4, (F5) 5, (F6) Back, (F7) Purchase");
	attroff(COLOR_PAIR(1));
	/*while(ch = getch())
	{	 switch(ch)
		{ case KEY_F(1):
		   research_hardware(1);
		   ingame_research_hardware_menu();
		   return 0;
		   break;
		 case KEY_F(2):
		   research_hardware(2);
		   ingame_research_hardware_menu();
		   return 0;
		   break;
		 case KEY_F(3):
		   research_hardware(3);
		   ingame_research_hardware_menu();
		   return 0;
		   break;
		 case KEY_F(4):
		   research_hardware(4);
		   ingame_research_hardware_menu();
		   return 0;
		   break;
		 case KEY_F(5):
		   research_hardware(5);
		   ingame_research_hardware_menu();
		   return 0;
		   break;
		 case KEY_F(6):
		   ingame_purchase_menu(1);
		   return 0;
		   break;
		 case KEY_F(7):
		   ingame_purchase_hardware_menu(0);
		   return 0;
		   break;
		}

	}*/

}

