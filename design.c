#include <ncurses.h>
#include "design.h"

void colors()
{
	start_color();

	init_pair(1,COLOR_WHITE,COLOR_YELLOW);
	init_pair(2,COLOR_GREEN,COLOR_GREEN);
	init_pair(3,COLOR_YELLOW,COLOR_YELLOW);

	init_pair(4,COLOR_RED,COLOR_RED);
	init_pair(5,COLOR_CYAN,COLOR_CYAN);
	init_pair(6,COLOR_MAGENTA,COLOR_MAGENTA);

	init_pair(7,COLOR_WHITE,COLOR_WHITE);
	init_pair(8,COLOR_BLUE,0);
	init_pair(9,COLOR_MAGENTA,0);

	init_pair(10,COLOR_WHITE,COLOR_GREEN);
	init_pair(11,COLOR_WHITE,COLOR_RED);
	init_pair(12,COLOR_BLUE,COLOR_BLUE);

	init_pair(14,COLOR_MAGENTA,0);
	init_pair(15,COLOR_WHITE,0);
}

void text1(int y, int x)
{
	int i;
	
	char U[10][100]={
	{"______       _   _   _           _     _	       "},
	{"| ___ \\     | | | | | |         | |   (_)           "},
	{"| |_/ / __ _| |_| |_| | ___  ___| |__  _ _ __        "},
	{"| ___ \\/ _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\   "},
	{"| |_/ / (_| | |_| |_| |  __/\\__ \\ | | | | |_) |    "},
	{"\\____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/  "},
        {"                                        |_|          "}
	};

	for(i=0;i<7;i++)
		mvprintw(y+i,x,U[i]);
}

void text2(int y, int x, WINDOW *c)
{
	draw(y,x,2,c);
	draw(y,x+1,2,c);
	draw(y,x+2,2,c);
	draw(y,x+3,2,c);
	draw(y+1,x,2,c);
	draw(y+1,x+3,2,c);
	draw(y+2,x,2,c);
	draw(y+2,x+1,2,c);
	draw(y+2,x+2,2,c);
	draw(y+3,x,2,c);
	draw(y+3,x+3,2,c);
	draw(y+4,x,2,c);
	draw(y+4,x+1,2,c);
	draw(y+4,x+2,2,c);
	draw(y+4,x+3,2,c);

	draw(y,x+5,4,c);
	draw(y,x+6,4,c);
	draw(y,x+7,4,c);
	draw(y,x+8,4,c);
	draw(y+1,x+5,4,c);
	draw(y+1,x+8,4,c);
	draw(y+2,x+5,4,c);
	draw(y+2,x+6,4,c);
	draw(y+2,x+7,4,c);
	draw(y+2,x+8,4,c);
	draw(y+3,x+5,4,c);
	draw(y+3,x+8,4,c);
	draw(y+4,x+5,4,c);
	draw(y+4,x+8,4,c);

	draw(y,x+10,12,c);
	draw(y,x+11,12,c);
	draw(y,x+12,12,c);
	draw(y,x+13,12,c);
	draw(y,x+14,12,c);
	draw(y+1,x+12,12,c);
	draw(y+2,x+12,12,c);
	draw(y+3,x+12,12,c);
	draw(y+4,x+12,12,c);

	draw(y,x+16,3,c);
	draw(y,x+17,3,c);
	draw(y,x+18,3,c);
	draw(y,x+19,3,c);
	draw(y,x+20,3,c);
	draw(y+1,x+18,3,c);
	draw(y+2,x+18,3,c);
	draw(y+3,x+18,3,c);
	draw(y+4,x+18,3,c);

	draw(y,x+22,6,c);
	draw(y+1,x+22,6,c);
	draw(y+2,x+22,6,c);
	draw(y+3,x+22,6,c);
	draw(y+4,x+22,6,c);
	draw(y+4,x+23,6,c);
	draw(y+4,x+24,6,c);
	draw(y+4,x+25,6,c);
	
	draw(y,x+27,4,c);
	draw(y,x+28,4,c);
	draw(y,x+29,4,c);
	draw(y,x+30,4,c);
	draw(y+1,x+27,4,c);
	draw(y+2,x+27,4,c);
	draw(y+2,x+28,4,c);
	draw(y+2,x+29,4,c);
	draw(y+2,x+30,4,c);
	draw(y+3,x+27,4,c);
	draw(y+4,x+27,4,c);
	draw(y+4,x+28,4,c);
	draw(y+4,x+29,4,c);
	draw(y+4,x+30,4,c);

	draw(y,x+32,12,c);
	draw(y,x+33,12,c);
	draw(y,x+34,12,c);
	draw(y,x+35,12,c);
	draw(y+1,x+32,12,c);
	draw(y+2,x+32,12,c);
	draw(y+2,x+33,12,c);
	draw(y+2,x+34,12,c);
	draw(y+2,x+35,12,c);
	draw(y+3,x+35,12,c);
	draw(y+4,x+32,12,c);
	draw(y+4,x+33,12,c);
	draw(y+4,x+34,12,c);
	draw(y+4,x+35,12,c);

	draw(y,x+37,2,c);
	draw(y+1,x+37,2,c);
	draw(y+2,x+37,2,c);
	draw(y+3,x+37,2,c);
	draw(y+4,x+37,2,c);
	draw(y,x+40,2,c);
	draw(y+1,x+40,2,c);
	draw(y+2,x+40,2,c);
	draw(y+3,x+40,2,c);
	draw(y+4,x+40,2,c);
	draw(y+2,x+38,2,c);
	draw(y+2,x+39,2,c);

	draw(y,x+42,3,c);
	draw(y+1,x+42,3,c);
	draw(y+2,x+42,3,c);
	draw(y+3,x+42,3,c);
	draw(y+4,x+42,3,c);

	draw(y,x+44,6,c);
	draw(y+1,x+44,6,c);
	draw(y+2,x+44,6,c);
	draw(y+3,x+44,6,c);
	draw(y+4,x+44,6,c);
	draw(y,x+45,6,c);
	draw(y,x+46,6,c);
	draw(y,x+47,6,c);
	draw(y+1,x+47,6,c);
	draw(y+2,x+45,6,c);
	draw(y+2,x+46,6,c);
	draw(y+2,x+47,6,c);
}

void text3(int y, int x)
{
	int i;
	
	char B[10][100]={
	{"______ _  __  __ _            _ _             "},
	{"|  _  (_)/ _|/ _(_)          | | |            "},
	{"| | | |_| |_| |_ _  ___ _   _| | |_ _   _     "},
	{"| | | | |  _|  _| |/ __| | | | | __| | | |    "},
	{"| |/ /| | | | | | | (__| |_| | | |_| |_| |    "},
	{"|___/ |_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |"},
	{"                                     __/_|    "}
	};

	for(i=0;i<7;i++)
		mvprintw(y+i,x,B[i]);

}

void text4(int y, int x)
{
	int i;

	char C[10][100]={
	{" _____                                          _     	"},
	{"|  __ \\                                        | |     	"},	
	{"| |  \\/ __ _ _ __ ___   ___ _ __ ___   ___   __| | ___ 	"},
	{"| | __ / _` | '_ ` _ \\ / _ \\ '_ ` _ \\ / _ \\ / _` |/ _ \\	"},
	{"| |_\\ \\ (_| | | | | | |  __/ | | | | | (_) | (_| |  __/	"},
	{" \\____/\\__,_|_| |_| |_|\\___|_| |_| |_|\\___/ \\__,_|\\___| "}
	};
                                                       
        for(i=0;i<6;i++)
		mvprintw(y+i,x,C[i]);                                               
}

void text5(int y, int x, WINDOW *c)
{
	draw(y-2,x,12,c);
	draw(y-2,x+1,12,c);
	draw(y-2,x+2,12,c);
	draw(y-1,x,12,c);
	draw(y,x,12,c);
	draw(y,x+1,12,c);
	draw(y,x+2,12,c);
	draw(y+1,x+2,12,c);
	draw(y+2,x+2,12,c);
	draw(y+2,x+1,12,c);
	draw(y+2,x,12,c);

	draw(y,x+4,3,c);
	draw(y,x+5,3,c);
	draw(y,x+6,3,c);
	draw(y+1,x+4,3,c);
	draw(y+2,x+4,3,c);
	draw(y+2,x+5,3,c);
	draw(y+2,x+6,3,c);

	draw(y,x+8,2,c);
	draw(y,x+9,2,c);
	draw(y,x+10,2,c);
	draw(y+1,x+8,2,c);
	draw(y+1,x+10,2,c);
	draw(y+2,x+8,2,c);
	draw(y+2,x+9,2,c);
	draw(y+2,x+10,2,c);

	draw(y,x+12,4,c);
	draw(y+1,x+12,4,c);
	draw(y,x+13,4,c);
	draw(y+1,x+14,4,c);
	draw(y+2,x+12,4,c);
	draw(y+2,x+14,4,c);

	draw(y,x+17,6,c);
	draw(y+2,x+17,6,c);
}

void text6(int y, int x)
{
	int i;

	char D[10][100]={
	{"__   __                                _   __  	"},
	{"\\ \\ / /                               | |  \\ \\    "},
	{" \\ V /___  _   _  __      _____  _ __ | | (_) |      "},
	{"  \\ // _ \\| | | | \\ \\ /\\ / / _ \\| '_ \\| |   | |  "},
	{"  | | (_) | |_| |  \\ V  V / (_) | | | |_|  _| |	"},
	{"  \\_/\\___/ \\__,_|   \\_/\\_/ \\___/|_| |_(_) (_) | "},
        {"                                           /_/ 	"}                                 
	};

	for(i=0;i<7;i++)
		mvprintw(y+i,x,D[i]); 
}

void text7(int y, int x)
{
	int i;

	char E[10][100]={	
	{"__   __            _           _   _      __	       "},
	{"\\ \\ / /           | |         | | | |  _ / /       "},
	{" \\ V /___  _   _  | | ___  ___| |_| | (_) |	       "},
	{"  \\ // _ \\| | | | | |/ _ \\/ __| __| |   | |       "},
	{"  | | (_) | |_| | | | (_) \\__ \\ |_|_|  _| |        "},
	{"  \\_/\\___/ \\__,_| |_|\\___/|___/\\__(_) (_) |     "},
        {"                                        \\_\\        "}
	};
                                            
	for(i=0;i<7;i++)
		mvprintw(y+i,x,E[i]); 
}

void text8(int y, int x)
{
	int i;

	char F[10][100]={
	{" _____      _           _                                         "},
	{"/  ___|    | |         | |                                        "},
	{"\\ `--.  ___| | ___  ___| |_    __ _   _ __ ___   __ _ _ __       "},
	{" `--. \\/ _ \\ |/ _ \\/ __| __|  / _` | | '_ ` _ \\ / _` | '_ \\  "},
	{"/\\__/ /  __/ |  __/ (__| |_  | (_| | | | | | | | (_| | |_) |     "},
	{"\\____/ \\___|_|\\___|\\___|\\__|  \\__,_| |_| |_| |_|\\__,_| .__/"},
	{"                                                     |_|          "}
	};

	for(i=0;i<7;i++)
		mvprintw(y+i,x,F[i]); 
}

void draw(int y, int x, int color, WINDOW *c)
{
	mvwin(c,y,x);
	wbkgd(c,COLOR_PAIR(color));
	
	refresh();
	wrefresh(c);
}
