struct player_info {
	int human;					 /* 1=human 2=ai */
	int nation;					 /* 1=no nation, 2=usa, 3=ussr */
	int currentbudget;			 /* current allocated budget for the year */
	int nextbudget;				 /* projected budget for next year */
	int prestige;				 /* prestige points earned */
	int cash;					 /* cash available */
	int endturn;				 /* end of turn flag */
	int launchpads;				 /* nulber of launchpads available */
	int hasmissions;
	int mission1id;
	char *mission1desc;
	int mission2id;
	int mission3id;
	int futuremission1id;
	char *futuremission1desc;
	int futuremission2id;
	int futuremission3id;
	int hasfuturemissions;
};

struct game_info {
	int year;					 /* year of the game */
	int season;					 /* season of the game */
};

struct hardware {
	char name[20];
	char type[10];
	int cost;					 /* initial cost */
	int unit;					 /* cost per unit */
	int safety;					 /* current safety rating */
	int rdcost;					 /* cost per r&d team */
	int weight;
	int payload;				 /* max carry weight */
	int rdmax;					 /* max safety by r&d */
	int safetymax;				 /* max possible safety */
	int onhand;					 /* units on hand */
	int maxduration;			 /* max time unit can spend in space */
	int crew;					 /* number of astronauts needed */
	int id;
	int category;
	int tid;
};

struct mission {
	int type;					 /* type of mission */
	int duration;				 /* mission duration */
	int joint;					 /* joint mission flag */
	int prestigef;				 /* prestige reward for first */
	int prestige;				 /* subsequent prestige */
	char *name;
	int id;
	int steps;
	int rocket;
	int rocketid;
	int booster;
};

struct launchpad {
	int inuse;
	int currentmissionid;
	int nextmissionid;
};

struct player_info player1;
struct player_info player2;
struct player_info *currentplayer;

struct game_info currentgame;
/*
struct hardware atlas;
struct hardware titan;
struct hardware saturnv;
struct hardware nova;
struct hardware strapon;
struct hardware explorer;
struct hardware ranger;
struct hardware surveyor;
struct hardware mercury;
struct hardware gemini;
struct hardware apollo;
struct hardware xms2;
struct hardware jupiter;
struct hardware eagle;
struct hardware cricket;
struct hardware kickera;
struct hardware kickerb;
struct hardware eva;
struct hardware dock;*/
struct hardware *currenthardware;
struct mission orbitalsatellite;
struct mission *currentmission;
struct launchpad lpusa1;
struct launchpad lpussr1;

void purchase_hardware (int units);
void research_hardware (int units);

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
WINDOW *top_win;
int top_win_startx, top_win_starty, top_win_width, top_win_height;
WINDOW *middle_win;
int middle_win_startx, middle_win_starty, middle_win_width, middle_win_height;
WINDOW *bottom_win;
WINDOW *middle_win_tmp;
int (*fptr)(int);

static int amountofrockets = 7;
