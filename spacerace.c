#include <ncurses.h>
#include <string.h>
#include "ui_helper.h"
#include "version.h"
#include "space.h"
#include <stdlib.h>
#include <time.h>
#include "menus.h"

struct hardware rocket[]=
{
	{"Atlas Rocket","Rockets",24,3,0,2,0,600,84,98,0,0,0,1,1,0},
	{"Titan Rocket","Rockets",60,12,0,4,0,1500,90,98,0,0,0,2,1,1},
	{"Saturn V Rocket","Rockets",84,18,0,6,0,3200,95,98,0,0,0,3,1,2},
	{"Nova","Rockets",150,30,0,8,0,4800,95,98,0,0,0,4,1,3},
	{"Strap-On Boosters","Rockets",12,3,0,2,0,1000,85,98,0,0,0,5,1,4},
};

struct hardware unmanned[]=
{
	{"Explorer Satellite","Unmanned",6,1,0,1,300,0,95,98,0,0,0,6,2,0},
	{"Ranger Satellite","Unmanned",24,4,0,3,700,0,90,93,0,0,0,7,2,1},
	{"Surveyor Probe","Unmanned",30,6,0,4,1200,0,85,88,0,0,0,8,2,2},
};

struct hardware capsule[]=
{
	{"Mercury Capsule","Capsules",18,2,0,1,500,0,80,90,0,0,1,9,3,0},
	{"Gemini Capsule","Capsules",24,6,0,2,1200,0,84,94,0,0,2,10,3,1},
	{"Apollo Capsule","Capsules",36,12,0,5,1600,0,87,94,0,0,3,11,3,2},
	{"XMS-2 Minishuttle","Capsules",60,30,0,7,1500,0,91,94,0,0,0,12,3,3},
	{"Jupiter Spacecraft","Capsules",60,30,0,7,4300,0,89,94,0,0,0,13,3,4},
	{"Eagle Module","Capsules",30,8,0,2,1500,0,90,94,0,0,2,14,3,5},
	{"Cricket Module","Capsules",42,8,0,4,1000,0,90,94,0,0,2,15,3,6},
};

struct hardware misc[]=
{
	{"Kicker-A Booster","Misc",12,3,0,1,300,0,94,97,0,0,0,16,4,0},
	{"Kicker-B Booster","Misc",18,6,0,2,600,0,94,96,0,0,0,17,4,1},
	{"EVA Suit","Misc",18,0,0,1,0,0,91,94,0,0,0,18,4,2},
	{"Docking Module","Misc",18,2,0,0,300,0,0,93,0,0,0,19,4,3},
};


int main(int argc, char *argv[])
{
	initCurses(); /* Begin curses mode */

	top_win = create_newwin(2, COLS, 0, 0);
	middle_win = create_newwin(LINES-2, COLS, 1, 0);
	bottom_win = create_newwin(2, COLS, LINES-1, 0);


	refresh();

	main_menu();

	endwin();	/* End curses mode */
	return 0;
}


WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	wrefresh(local_win);

	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window
	 * 3. rs: character to be used for the right side of the window
	 * 4. ts: character to be used for the top side of the window
	 * 5. bs: character to be used for the bottom side of the window
	 * 6. tl: character to be used for the top left corner of the window
	 * 7. tr: character to be used for the top right corner of the window
	 * 8. bl: character to be used for the bottom left corner of the window
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}


int playgame ()
{
	player1.currentbudget = 60;			 // setting the starting values
	player2.currentbudget = 60;			 // of player budget, cash and
	player1.cash = 60;					 // lauchpads
	player2.cash = 60;
	player1.launchpads = 1;
	player2.launchpads = 1;
	currentplayer = &player1;			 // player 1 goes first

	if (currentplayer->nation == 2)		 // depending on the nation of
	{									 // player 1, set nation of player 2
		player2.nation = 3;
	}
	else
	{
		player2.nation = 2;
	}

	currentgame.year = 1957;			 // start the game in spring 1957
	currentgame.season = 1;


	orbitalsatellite.name = "Orbital Satellite";
	orbitalsatellite.id = 1;
	orbitalsatellite.steps = 2;


	while (currentgame.year < 1975)				 // game runs until 1975
	{
		while (currentplayer->endturn == 0)		 // stay in main menu until endturn flag
		{										 // is set to 1
			ingame_main_menu ();
		}
		currentplayer->endturn = 0;				 // reset it to 0
		currentplayer->hasmissions = currentplayer->hasfuturemissions;
		currentplayer->mission1id = currentplayer->futuremission1id;
		currentplayer->mission1desc = currentplayer->futuremission1desc;
		currentplayer->hasfuturemissions = 0;
		currentplayer = &player2;				 // and change player
		while (currentplayer->endturn == 0)
		{
			ingame_main_menu ();
		}
		currentplayer->endturn = 0;
		currentplayer = &player1;
		if (currentplayer->hasmissions = 1)
		{
			ingame_launch_mission_menu();
		}
		if (currentgame.season == 1)			 // after a turn each, change season
		{
			currentgame.season = 2;
		}
		else									 // or year
		{
			currentgame.season = 1;
			currentgame.year++;
		}
	}										 // and start again


}






// this is run when a player buys new hardware
void purchase_hardware (int units)
{
	// is it the first purchase of this hardware?
	if (currenthardware->onhand == 0 && currenthardware->safety == 0)
	{
		if ((currenthardware->cost + currenthardware->unit * (units - 1)) > currentplayer->cash)
		{
			// do nothing if player can't afford it
		}
		else
		{	//otherwise increase number of units available and decrease cash accordingly
			currenthardware->onhand = currenthardware->onhand + units;
			currentplayer->cash = currentplayer->cash - (currenthardware->cost + currenthardware->unit * (units - 1));
			// here we are setting initial hardware safety
			if (currenthardware->id == 1)
			{
				currenthardware->safety = 10;
			}
			else if (currenthardware->id == 2)
			{
				if (rocket[0].safety >= 75)
				{
					currenthardware->safety = 35;
				}
				else
				{
					currenthardware->safety = 10;
				}
			}
			else if (currenthardware->id == 3)
			{
				if (rocket[0].safety >= 75 && rocket[1].safety < 75)
				{
					currenthardware->safety = 25;
				}
				else if (rocket[0].safety < 75 && rocket[1].safety >= 75)
				{
					currenthardware->safety = 45;
				}
				else if (rocket[0].safety >= 75 && rocket[1].safety >= 75)
				{
					currenthardware->safety = 70;
				}
				else
				{
					currenthardware->safety = 10;
				}
			}
			else if (currenthardware->id == 6)
			{
				currenthardware->safety = 40;
			}
		}
	}
	else  // ok so it's not the first purchase, no need to worry about safety
	{
		if ((currenthardware->unit * units) > currentplayer->cash || currenthardware->safety >= currenthardware->safetymax)
		{
			// player can't afford it, do nothing
		}
		else // otherwise increase units on hand and decrease cash
		{
			currenthardware->onhand = currenthardware->onhand + units;
			currentplayer->cash = currentplayer->cash - currenthardware->unit * units;
		}
	}
}

// this is run when a player does research
void research_hardware (int units)
{

	if (currenthardware->onhand == 0 && currenthardware->safety == 0)
	{
	// if the player hasn't bought the hardware at all yet, do nothing
	}

	else
	{	// otherwise check that he can afford it
		if ((currenthardware->rdcost * units) > currentplayer->cash  || currenthardware->safety >= currenthardware->rdmax)
		{
			// do nothing if he can't
		}
		else
		{  // or calculate effectiveness of r&d, 1d6 per team
			int x = 0;
			int rd=0, rdt=0;
			while (x < units)
			{
				srand ( time(NULL) );
				rd = rand() % 6 + 1;
				rdt = rdt + rd;
				x++;
			}
			if (currenthardware->safety + rdt < currenthardware->rdmax)
			{  // as long as new safety isn't more than max r&d safety
			   // increase it and deduct cash
				currenthardware->safety = currenthardware->safety + rdt;
				currentplayer->cash = currentplayer->cash - currenthardware->rdcost * units;
			}
			else
			{  // otherwise, set to max r&d safety and deduct cash
				currenthardware->safety = currenthardware->rdmax;
				currentplayer->cash = currentplayer->cash - currenthardware->rdcost * units;
			}
		}
	}
}

// this is run when a player buys a new launchpad
void buy_launchpad(int highlighted)
{
	if (currentplayer->cash < 20)  // can he afford it?
	{
	}
	else
	{
		currentplayer->cash = currentplayer->cash - 20;  // deduct cash
		currentplayer->launchpads++;					 // and increase his launchpads
	}
	ingame_future_launch_menu(highlighted);
}

void assign_mission(int launchpad, int mission_id)
{
	switch(launchpad)
	{
		case 1:
			currentplayer->hasfuturemissions = 1;
			currentplayer->futuremission1id = mission_id;
			currentplayer->futuremission1desc = currentmission->name;
			break;
		case 2:
			currentplayer->hasfuturemissions = 1;
			currentplayer->futuremission2id = mission_id;
			break;
		case 3:
			currentplayer->hasfuturemissions = 1;
			currentplayer->futuremission3id = mission_id;
			break;
	}
}

int launch_mission()
{
	int i = 1;
	int rd=0, rdt=0;
	int success = 2;
	srand ( time(NULL) );
	while (i <= currentmission->steps)
	{
		rd = rand() % 100 + 1;
		//rdt = rdt + rd;
		if (rd > currenthardware->safety && i == 0)
		{
			success = -1;
			return 0;
		}
		else if (rd > currenthardware->safety && i == 1)
		{
			success = 0;
		}
		currenthardware = &unmanned[1];
		i++;
	}
	return success;
}
