#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "randomize.h"
#include "design.h"
#include "menu.h"
#include "game.h"


int main(int argc, char **argv)
{
	if(argc==1)
	{
		printf("[Eroare]: Nu s-au dat argumente de comanda.");

		return 1;
	}

	int f;

	for(f=1;f<argc;f++)
	{
		FILE *myFile=fopen(argv[f],"r");

		if(myFile==NULL)
		{
			printf("[Eroare]: Fisierul %s nu poate fi deschis.",argv[f]);

			return 1;
		}
		else
			fclose(myFile);
	}

	srand(time(NULL));

	initscr();

	cbreak();
	noecho();

	keypad(stdscr,TRUE); 
	colors();
	
	int new_round=1, map_no, dif=1, mode=1;
	char R[10][10];

	menu_(argc,argv,&new_round,&map_no,&dif,&mode,R);

	endwin();

	return 0;
}
