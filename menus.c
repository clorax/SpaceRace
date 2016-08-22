#include "ui_helper.h"
#include <ncurses.h>
#include <string.h>
#include "space.h"
#include "menus.h"
#include "version.h"

extern struct hardware rocket[];
extern struct hardware unmanned[];
extern struct hardware capsule[];
extern struct hardware misc[];
WINDOW *middle2_win;


int main_menu ()
{
	clearScreen(0, "Welcome to the Space Race", "version " VERSION, "");
	int highlighted = 1;
	int items = 6;
	int size = 12;
	char mainmenu[6][12] = {"","New Game","Old Game","Multiplayer","Credits","Exit"};

	highlighted = drawmenu(items,size,highlighted,mainmenu);

	switch(highlighted)
	{
		case 3:
			multiplayer_menu();
			return 0;
			break;
	}

}

int multiplayer_menu ()
{
	clearScreen(0, "Space Race Multiplayer", "version " VERSION, "");
	char test[4][10] = {"","Hot Seat","Connect","Main menu"};
	int highlighted = 1;
	int items = 4;
	int size = 10;
	highlighted = drawmenu(items,size,highlighted,test);

	switch(highlighted)
	{
		case 1:
			nation_menu();
			return 0;
			break;
		case 2:
			break;
		case 3:
			main_menu();
			return 0;
			break;
	}

}


int nation_menu ()
{
	clearScreen(0, "Space Race Nation Selection", "version " VERSION, "");
	char test[4][9] = {"","U.S.A.","U.R.S.S.","Back"};
	int highlighted = 1;
	int items = 4;
	int size = 9;
	highlighted = drawmenu(items,size,highlighted,test);

	switch(highlighted)
	{
		case 1:
			player1.nation = 2;
			playgame();
			return 0;
			break;
		case 2:
			player1.nation = 3;
			playgame();
			return 0;
			break;
		case 3:
			multiplayer_menu();
			return 0;
			break;
	}

}


int ingame_main_menu ()
{
	clearScreen(currentplayer->nation,"Administration","","");

	char test[9][23] = {"","Budget Office","Hardware Purchase","Research & Development","Future Missions","Astronaut Recruiting","Vehicle Assembly","Mission Control","End Turn"};
	int highlighted = 1;
	int items = 9;
	int size = 23;
	highlighted = drawmenu(items,size,highlighted,test);

	switch(highlighted)
	{
		case 1:
			ingame_budget_menu();
			return 0;
			break;
		case 2:
			ingame_purchase_menu(0);
			return 0;
			break;
		case 3:
			ingame_purchase_menu(1);
			return 0;
			break;
		case 4:
			ingame_future_launch_menu(0);
			return 0;
			break;
		case 5:
			//ingame_recruiting_menu();
			break;
		case 6:
			//ingame_assembly_menu();
			break;
		case 7:
			//ingame_control_menu();
			break;
		case 8:
			//ingame_endturn_menu();
			currentplayer->endturn = 1;
			return 0;
			break;
	}


}


int ingame_purchase_menu (int rd)
{
	if (rd == 0)		  // purchase and r&d both use this functon to draw their menu
	{					  // so an r&d flag is needed, set to 1 if r&d
		clearScreen(currentplayer->nation,"Purchase Hardware","","");
	}
	else
	{
		clearScreen(currentplayer->nation,"Research & Development","","");
	}

	char test[6][9] = {"","Unmanned","Rockets","Capsules","Misc","Back"};
	int highlighted = 1;
	int items = 6;
	int size = 9;
	currenthardware = &unmanned[0];

	highlighted = drawmenuc(items,size,highlighted,test);

	switch(highlighted)
	{
		case 1:
			ingame_purchase_unmanned_menu(rd);
			return 0;
			break;
		case 2:
			ingame_purchase_rockets_menu(rd);
			return 0;
			break;
		case 3:
			ingame_purchase_capsules_menu(rd);
			return 0;
			break;
		case 4:
			ingame_purchase_misc_menu(rd);
			return 0;
			break;
		case 5:
			return 0;
			break;
	}


}


int ingame_purchase_rockets_menu(int rd)
{
	if (rd == 0)
	{
		clearScreen(currentplayer->nation,"Purchase Hardware -> Rockets","","");
	}
	else
	{
		clearScreen(currentplayer->nation,"Research & Develoment -> Rockets","","");
	}
	char test[7][17] = {"","Atlas Rocket","Titan Rocket","Saturn V Rocket","Nova Rocket","Booster Strap-On","Back"};
	int highlighted = 1;
	int items = 7;
	int size = 17;
	highlighted = drawmenu(items,size,highlighted,test);

	currenthardware = &rocket[highlighted-1];
	ingame_purchase_hardware_menu(rd);
	return 0;

}


int ingame_purchase_unmanned_menu(int rd)
{
	if (rd == 0)
	{
		clearScreen(currentplayer->nation,"Purchase Hardware -> Unmanned","","");
	}
	else
	{
		clearScreen(currentplayer->nation,"Research & Develoment -> Unmanned","","");
	}
	char test[5][19] = {"","Explorer Satellite","Ranger Satellite","Surveyor Probe","Back"};
	int highlighted = 1;
	int items = 5;
	int size = 19;
	highlighted = drawmenu(items,size,highlighted,test);
	currenthardware = &unmanned[highlighted-1];
	ingame_purchase_hardware_menu(rd);
	return 0;
}


int ingame_purchase_capsules_menu(int rd)
{
	middle2_win = create_newwin(LINES-2/2, COLS, LINES/2, 0);

	if (rd == 0)
	{
		clearScreen(currentplayer->nation,"Purchase Hardware -> Capsules","","");
	}
	else
	{
		clearScreen(currentplayer->nation,"Research & Develoment -> Capsules","","");
	}
	char test[9][19] = {"","Mercury Capsule","Gemini Capsule","Apollo Capsule","XMS-2 Minishuttle","Jupiter Spacecraft","Eagle Module","Cricket Module","Back"};
	int highlighted = 1;
	int items = 9;
	int size = 19;
	highlighted = drawmenu(items,size,highlighted,test);

	wrefresh(middle2_win);
	currenthardware = &capsule[highlighted-1];
	ingame_purchase_hardware_menu(rd);
	return 0;
}


int ingame_purchase_misc_menu(int rd)
{
	if (rd == 0)
	{
		clearScreen(currentplayer->nation,"Purchase Hardware -> Misc","","");
	}
	else
	{
		clearScreen(currentplayer->nation,"Research & Development -> Misc","","");
	}
	char test[6][17] = {"","Kicker-A Booster","Kicker-B Booster","EVA Suit","Docking Module","Back"};
	int highlighted = 1;
	int items = 6;
	int size = 17;
	int ch;
	//while (ch = getch())
	//{
	//fptr = ingame_purchase_misc_menu;
	while (highlighted != -1)
	{
		highlighted = drawmenun(items,size,highlighted,test);
		if (highlighted == -1 || highlighted == items-1)
		{
			werase(middle2_win);
		}else{
			currenthardware = &misc[highlighted-1];
			ingame_purchase_hardware_menu(rd);
		}
	}
	//return 0;
	// }
}


void ingame_purchase_hardware_menu( int rd)
{
	if (rd == 1) // do we actually want the r&d menu?
	{
		ingame_research_hardware_menu();
		//return 0;
	}
	//clearScreen(currentplayer->nation,"","","");
	int ch;

	attron(COLOR_PAIR(currentplayer->nation));
	attron(WA_REVERSE);
	mvprintw(0,1,"Purchase Hardware -> %s -> %s", currenthardware->type, currenthardware->name);
	attroff(COLOR_PAIR(currentplayer->nation));
	attroff(WA_REVERSE);


	attron(COLOR_PAIR(1));
	if (currenthardware->onhand == 0 && currenthardware->safety == 0)
	{
		attron(COLOR_PAIR(3));
		mvwprintw(middle2_win,3,1,"No program initiated");
		attroff(COLOR_PAIR(3));
	}
	else
	{
		attron(COLOR_PAIR(4));
		mvwprintw(middle2_win,3,1,"Units on hand: %d", currenthardware->onhand);
		attroff(COLOR_PAIR(4));
	}
	attron(COLOR_PAIR(1));
	mvwprintw(middle2_win,4,1, "Inital cost: %d", currenthardware->cost);
	mvwprintw(middle2_win,5,1, "Unit cost: %d", currenthardware->unit);
	if (currenthardware->safety > 75)
	{
		attron(COLOR_PAIR(4));
		mvwprintw(middle2_win,6,1, "Safety factor: %d %", currenthardware->safety);
		attroff(COLOR_PAIR(4));
	}
	else
	{
		attron(COLOR_PAIR(3));
		mvwprintw(middle2_win,6,1, "Safety factor: %d %", currenthardware->safety);
		attroff(COLOR_PAIR(3));
	}
	attron(COLOR_PAIR(1));
	mvwprintw(middle2_win,7,1, "R&D cost per team: %d", currenthardware->rdcost);
	if (currenthardware->weight == 0)
	{
		mvwprintw(middle2_win,8,1, "Unit weight: N/A");
	}
	else
	{
		mvwprintw(middle2_win,8,1, "Unit weight: %d", currenthardware->weight);
	}
	if (currenthardware->payload == 0)
	{
		mvwprintw(middle2_win,9,1, "Maximum payload: N/A");
	}
	else
	{
		mvwprintw(middle2_win,9,1, "Maximum payload: %d", currenthardware->payload);
	}
	mvwprintw(middle2_win,10,1, "Maximum R&D: %d %", currenthardware->rdmax);
	mvwprintw(middle2_win,11,1, "Maximum safety: %d %", currenthardware->safetymax);
	printCenter(12,0,0,"(F1)Purchase 1, (F2) 2, (F3) 3, (F4) 4, (F5) 5, (F6) Back, (F7) R&D");
	attroff(COLOR_PAIR(1));
	wrefresh(middle2_win);
	/* while(*/ch = getch();/*)
	{ */
	switch(ch)
		{
			case KEY_F(1):
				purchase_hardware(1);
				ingame_purchase_hardware_menu(rd);
				//return 0;
				break;
			case KEY_F(2):
				purchase_hardware(2);
				ingame_purchase_hardware_menu(rd);
				return 0;
				break;
			case KEY_F(3):
				purchase_hardware(3);
				ingame_purchase_hardware_menu(rd);
				return 0;
				break;
			case KEY_F(4):
				purchase_hardware(4);
				ingame_purchase_hardware_menu(rd);
				return 0;
				break;
			case KEY_F(5):
				purchase_hardware(5);
				ingame_purchase_hardware_menu(rd);
				return 0;
				break;
			case KEY_F(6):
				ingame_purchase_menu(rd);
				return 0;
				break;
			case KEY_F(7):
				ingame_research_hardware_menu();
				return 0;
				break;

		}

   /* }*/

}


int ingame_budget_menu ()
{
	clearScreen(currentplayer->nation,"Budget Office","","");

	int ch;

	attron(COLOR_PAIR(1));
	mvprintw(7,1,"This year's current total budget is: %d MB.", currentplayer->currentbudget);
	mvprintw(8,1,"You have %d MB left to spend.", currentplayer->cash);
	attroff(COLOR_PAIR(1));

	while(ch = getch())
	{
		return 0;
	break;
	}


}


int ingame_research_hardware_menu()
{
	clearScreen(currentplayer->nation,"","","");
	int ch;
	//printCenter(2,0,0,"Atlas Rocket");
	attron(COLOR_PAIR(currentplayer->nation));
	attron(WA_REVERSE);
	mvprintw(0,1,"Research & Development -> %s -> %s", currenthardware->type, currenthardware->name);
	attroff(COLOR_PAIR(currentplayer->nation));
	attroff(WA_REVERSE);


	attron(COLOR_PAIR(1));
	if (currenthardware->onhand == 0 && currenthardware->safety == 0)
	{
		attron(COLOR_PAIR(3));
		mvprintw(3,1,"No program initiated");
		attroff(COLOR_PAIR(3));
	}
	else
	{
		attron(COLOR_PAIR(4));
		mvprintw(3,1,"Units on hand: %d", currenthardware->onhand);
		attroff(COLOR_PAIR(4));
	}
	attron(COLOR_PAIR(1));
	mvprintw(4,1, "Inital cost: %d", currenthardware->cost);
	mvprintw(5,1, "Unit cost: %d", currenthardware->unit);
	if (currenthardware->safety > 75)
	{
		attron(COLOR_PAIR(4));
		mvprintw(6,1, "Safety factor: %d %", currenthardware->safety);
		attroff(COLOR_PAIR(4));
	}
	else
	{
		attron(COLOR_PAIR(3));
		mvprintw(6,1, "Safety factor: %d %", currenthardware->safety);
		attroff(COLOR_PAIR(3));
	}
	attron(COLOR_PAIR(1));
	mvprintw(7,1, "R&D cost per team: %d", currenthardware->rdcost);
	if (currenthardware->weight == 0)
	{
		mvprintw(8,1, "Unit weight: N/A");
	}
	else
	{
		mvprintw(8,1, "Unit weight: %d", currenthardware->weight);
	}
	if (currenthardware->payload == 0)
	{
		mvprintw(9,1, "Maximum payload: N/A");
	}
	else
	{
		mvprintw(9,1, "Maximum payload: %d", currenthardware->payload);
	}
	mvprintw(10,1, "Maximum R&D: %d %", currenthardware->rdmax);
	mvprintw(11,1, "Maximum safety: %d %", currenthardware->safetymax);
	/*printCenter(6,0,0,"Rockets");
	printCenter(7,0,0,"Capsules");
	printCenter(8,0,0,"Misc");*/
	printCenter(12,0,0,"(F1)Research 1, (F2) 2, (F3) 3, (F4) 4, (F5) 5, (F6) Back, (F7) Purchase");
	attroff(COLOR_PAIR(1));
	while(ch = getch())
	{
		switch(ch)
		{
			case KEY_F(1):
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

	}

}

// launchpad menu, buy launchpads and schedule future missions
int ingame_future_launch_menu(int highlighted)
{
	clearScreen(currentplayer->nation,"Future Launch Selection","","");
	int ch,x,y;
	getmaxyx(middle_win, y, x);
	wattron(middle_win,COLOR_PAIR(currentplayer->nation));
	mvwvline(middle_win,0,20,0,y);
	mvwhline(middle_win,y/3,0,0,x);
	mvwhline(middle_win,y*2/3,0,0,x);
	mvwprintw(middle_win,y/6,5,"Pad A");
	mvwprintw(middle_win,y/2,5,"Pad B");
	mvwprintw(middle_win,y-3,5,"Pad C");
	wattroff(middle_win,COLOR_PAIR(currentplayer->nation));
	if (currentplayer->launchpads == 1)  // we have one launchpad
	{
		wattron(middle_win,COLOR_PAIR(3));
		mvwprintw(middle_win,y/2-1,25,"No facility exists");
		mvwprintw(middle_win,y-4,25,"No facility exists");
		wattroff(middle_win,COLOR_PAIR(3));
		wattron(middle_win,COLOR_PAIR(1));
		mvwprintw(middle_win,y/2,25,"You can purchase a launch pad for 20MB");
		mvwprintw(middle_win,y-3,25,"You can purchase a launch pad for 20MB");
		wattroff(middle_win,COLOR_PAIR(1));
		if (currentplayer->hasfuturemissions != 1)
		{
			wattron(middle_win,COLOR_PAIR(1));
			mvwprintw(middle_win,y/6,25,"None");
			wattroff(middle_win,COLOR_PAIR(1));
		}
		else
		{
			wattron(middle_win,COLOR_PAIR(1));
			mvwprintw(middle_win,y/6,25,"%s", currentplayer->futuremission1desc);
			wattroff(middle_win,COLOR_PAIR(1));
		}

	}
	else if (currentplayer->launchpads == 2) // or two
	{
		wattron(middle_win,COLOR_PAIR(1));
		mvwprintw(middle_win,y/2,25,"None");
		wattroff(middle_win,COLOR_PAIR(1));
		wattron(middle_win,COLOR_PAIR(3));
		mvwprintw(middle_win,y-4,25,"No facility exists");
		wattroff(middle_win,COLOR_PAIR(3));
		wattron(middle_win,COLOR_PAIR(1));
		mvwprintw(middle_win,y-3,25,"You can purchase a launch pad for 20MB");
		wattroff(middle_win,COLOR_PAIR(1));
	}
	else  // or all three
	{
		wattron(middle_win,COLOR_PAIR(1));
		mvwprintw(middle_win,y/2,25,"None");
		mvwprintw(middle_win,y-3,25,"None");
		wattroff(middle_win,COLOR_PAIR(1));
	}

	if (highlighted == 0) // if we came to this menu then this value will be 0
	{
		highlighted = y/3-1;  // so set it to the yoffset value below
	}					// that way the first menu entry will be selected
	fptr = ingame_future_launch_menu;  // pointer to this current function
	if (currentplayer->launchpads == 1)
	{
		char test[3][22] = {"Assign Future Mission","Purchase Launch Pad","Purchase Launch Pad"};
		highlighted = drawcustommenu(3,22,highlighted,test,y/3,y/3-1,30);
		switch(highlighted)
		{
			case 4:
				ingame_assign_mission_menu(1);
				return 0;
				break;
			case 10:
				buy_launchpad(highlighted);
				return 0;
				break;
			case 16:
				buy_launchpad(highlighted);
				return 0;
				break;
		}

	}
	else if (currentplayer->launchpads == 2)
	{
		char test[3][22] = {"Assign Future Mission","Assign Future Mission","Purchase Launch Pad"};
		highlighted = drawcustommenu(3,22,highlighted,test,6,4,30);

		switch(highlighted)
		{
			case 4:
				break;
			case 10:
				break;
			case 16:
				buy_launchpad(highlighted);
				return 0;
				break;
		}

	}
	else
	{
		char test[3][22] = {"Assign Future Mission","Assign Future Mission","Assign Future Mission"};
		drawcustommenu(3,22,highlighted,test,6,4,30);
	}



}


int ingame_assign_mission_menu(int launchpad)
{
	switch(launchpad)
	{
		case 1:
			clearScreen(currentplayer->nation,"Future Missions -> Launch Pad A","","");
			break;
		case 2:
			clearScreen(currentplayer->nation,"Future Missions -> Launch Pad B","","");
			break;
		case 3:
			clearScreen(currentplayer->nation,"Future Missions -> Launch Pad C","","");
			break;
	}

	char test[3][18] = {"","Orbital Satellite","Cancel"};
	int highlighted = 1;
	int items = 3;
	int size = 18;
	highlighted = drawmenu(items,size,highlighted,test);


	switch(highlighted)
	{
		case 1:
			currentmission = &orbitalsatellite;
			assign_mission(launchpad, 1);
			return 0;
			break;
		case 2:
			return 0;
			break;
	}

}

int ingame_launch_mission_menu()
{
	clearScreen(currentplayer->nation,"Mission Launch","","");
	int success;
	attron(COLOR_PAIR(1));
	mvprintw(3,1,"Launching %s", currentplayer->mission1desc);
	attroff(COLOR_PAIR(1));
	switch(currentplayer->mission1id)
	{
		case 1:
			currentmission = &orbitalsatellite;
			currenthardware = &rocket[0];
			success = launch_mission();
			break;
	}
	if (success == 0)
	{
		attron(COLOR_PAIR(3));
		mvprintw(5,1, "Satellite Failure!");
		attroff(COLOR_PAIR(3));
	}
	else if (success == 1)
	{
		attron(COLOR_PAIR(4));
		mvprintw(5,1, "Success!");
		attroff(COLOR_PAIR(4));
	}
	else
	{
		attron(COLOR_PAIR(4));
		mvprintw(5,1, "Rocket Failure!");
		attroff(COLOR_PAIR(4));
	}
	while(success = getch())
	{
		return 0;
	}
}
