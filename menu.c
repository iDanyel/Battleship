#include <ncurses.h>
#include <string.h>
#include "design.h"
#include "menu.h"
#include "game.h"

#define m_size1 4
#define m_size2 15

int map_selector(int argc, char **argv, int dif, int mode)
{
	int selected=0, c, start=1, no_, x, y, i;
	char v[15]="               ";

	WINDOW *a=newwin(3,10,0,0); box(a,0,0);
	WINDOW *b=newwin(1,1,0,0); box(a,0,0);

	while(start)
	{	
		int pos=12, l=7;

		clear(); getmaxyx(stdscr,y,x);

		mvprintw(y-2,x-23,"Apasa   pentru a iesi");

		attron(COLOR_PAIR(11));
		mvprintw(y-2,x-17,"q");
		attroff(COLOR_PAIR(11));

		text8(2,5);

		mvprintw(1,x/2+5,"Dificultate selectata: ");
		mvprintw(3,x/2+5,"Mod de joc selectat: ");

		int pair;

		attron(COLOR_PAIR(0));
		mvprintw(1,x/2+28,v);
		mvprintw(3,x/2+26,v);
		attroff(COLOR_PAIR(0));

		if(dif==1)
			pair=1;
		else if(dif==2)
			pair=10;
		else
			pair=11;

		attron(COLOR_PAIR(pair));

		if(dif==1)
			mvprintw(1,x/2+28,"Easy");
		else if(dif==1)
			mvprintw(1,x/2+28,"Medium");
		else
			mvprintw(1,x/2+28,"Hard");

		attroff(COLOR_PAIR(pair));

		if(mode==1)
			pair=10;
		else
			pair=11;

		attron(COLOR_PAIR(pair));
		
		if(mode==1)
			mvprintw(3,x/2+26,"Normal mode");
		else
			mvprintw(3,x/2+26,"Try hard mode");

		attroff(COLOR_PAIR(pair));

		for(i=3;i<67;i++)
			draw(9,i,7,b);

		for(i=0;i<y;i++)
			mvprintw(i,x/2,"|");

		for(i=0;i<argc-1;i++)
		{
			draw(pos-1,l-2,15,a);

			if(i==selected)
			{
				attron(COLOR_PAIR(11));
				mvprintw(pos,l,"Map %d",i+1);
				attroff(COLOR_PAIR(11));
			}
			else
				mvprintw(pos,l,"Map %d",i+1);

			l+=10;

			if(l>=x/2-10)
				pos+=5, l=7;
		}

		mvprintw(0,0,""); c=getch();
		
		if(c==KEY_LEFT)
		{
			if(selected==0)
				selected=argc-2;
			else
				selected--;
		}
		else if(c==KEY_RIGHT)
		{
			if(selected==argc-2)
				selected=0;
			else
				selected++;
		}
		else if(c==10)
			no_=selected+1, start=0;
		else if(c=='q')
			return 0;
	}

	delwin(a); delwin(b);

	return no_;
}

void s_menu_(int *dif, int *mode)
{
	clear();

	int start=1, line=0, column=0, c, d, x, y, i;
	char s_menu_[m_size1-1][m_size2], s_menu__[m_size1-2][m_size2], v[15]="               ";
	
	strcpy(s_menu_[0],"Easy"); strcpy(s_menu_[1],"Medium"); strcpy(s_menu_[2],"Hard");
	strcpy(s_menu__[0],"Normal mode"); strcpy(s_menu__[1],"Try hard mode"); 

	WINDOW *a=newwin(1,1,0,0); box(a,0,0);
	WINDOW *b=newwin(5,32,12,16); box(b,0,0);
	WINDOW *ab=newwin(5,32,28,16); box(ab,0,0);

	getmaxyx(stdscr,y,x);

	while(start)
	{
		d=20;

		refresh(); wrefresh(b); wrefresh(ab);
	        text3(2,11); text4(18,7);

		for(i=7;i<60;i++)
			draw(9,i,7,a);

		for(i=5;i<65;i++)
			draw(25,i,7,a);

		for(i=0;i<y;i++)
			mvprintw(i,x/2,"|");

		mvprintw(2,x/2+5,"* Navigarea se face utilizand sagetile.");
		mvprintw(4,x/2+5,"* Optiunea se alege apasand tasta enter.");
		mvprintw(8,x/2+5,"* Modul normal = numar nelimitat de greseli.");
		mvprintw(10,x/2+5,"* Modul try hard = maxim 15 greseli.");

		mvprintw(y-2,x/2-23,"Apasa   pentru a iesi");

		attron(COLOR_PAIR(11));
		mvprintw(y-2,x/2-17,"q");
		attroff(COLOR_PAIR(11));

		mvprintw(y-3,x/2+5,"Dificultate selectata: ");
		mvprintw(y-2,x/2+5,"Mod de joc selectat: ");

		int pair;

		attron(COLOR_PAIR(0));
		mvprintw(y-3,x/2+28,v);
		mvprintw(y-2,x/2+26,v);
		attroff(COLOR_PAIR(0));

		if(*dif==1)
			pair=1;
		else if(*dif==2)
			pair=10;
		else
			pair=11;

		attron(COLOR_PAIR(pair));
		mvprintw(y-3,x/2+28,s_menu_[*dif-1]);
		attroff(COLOR_PAIR(pair));

		if(*mode==1)
			pair=10;
		else
			pair=11;

		attron(COLOR_PAIR(pair));
		mvprintw(y-2,x/2+26,s_menu__[*mode-1]);
		attroff(COLOR_PAIR(pair));

		for(i=0;i<m_size1-1;i++)
		{
			if(line==0&&i==column)
			{
				int no_pair;

				if(column==0)
					no_pair=1;
				else if(column==1)
					no_pair=10;
				else
					no_pair=11;
					
				attron(COLOR_PAIR(no_pair));
				mvprintw(14,d,s_menu_[i]);
				attroff(COLOR_PAIR(no_pair));
			}
			else 
				mvprintw(14,d,s_menu_[i]);

			d+=10;
		}

		d=18;

		for(i=0;i<m_size1-2;i++)
		{
			if(line==1&&i==column)
			{
				int no_pair;
			
				if(column==0)
					no_pair=10;
				else
					no_pair=11;

				attron(COLOR_PAIR(no_pair));
				mvprintw(30,d,s_menu__[i]);
				attroff(COLOR_PAIR(no_pair));
			}
			else
				mvprintw(30,d,s_menu__[i]);

			d+=15;
		}

		mvprintw(0,0,""); c=getch();

		if(c==KEY_RIGHT)
		{
			if(line==0)
			{
				if(column+1<m_size1-1)
					column++;
				else
					column=0;
			}
			else
			{	
				if(column+1<m_size1-2)
					column++;
				else
					column=0;
			}

		}
		else if(c==KEY_LEFT)
		{
			if(line==0)
			{
				if(column-1>=0)
					column--;
				else
					column=m_size1-1;
			}
			else
			{
				if(column-1>=0)
					column--;
				else
					column=m_size1-2;
			}
		}
		else if(c==KEY_UP||c==KEY_DOWN)
		{
			if(line==0)
				line=1, column=0;
			else
				line=0, column=0;
		}
		else if(c==10)
		{
			if(line==0)
			{
				if(column==0)
					*dif=1;
				else if(column==1)
					*dif=2;
				else
					*dif=3;
			}
			else
			{
				if(column==0)
					*mode=1;
				else
					*mode=2;
			}

			beep();
		}
		else if(c=='q')
			start=0;
	}

	delwin(a);
	delwin(b);
	delwin(ab);
}

int menu_(int argc, char **argv, int *new_round, int *map_no, int *dif, int *mode, char R[][10])
{
	int k, start=1, line=0, x, y, c, i;
	char menu_[m_size1][m_size2];

	strcpy(menu_[0],"New Game"); strcpy(menu_[1],"Resume Game");
	strcpy(menu_[2],"Settings"); strcpy(menu_[3],"Quit");

	WINDOW *a=newwin(1,1,0,0); box(a,0,0);
	WINDOW *b=newwin(1,2,0,0); box(b,0,0);

        attron(A_BOLD);  
	
	while(start)
	{	
		clear(); getmaxyx(stdscr,y,x);
		refresh(); attroff(COLOR_PAIR(1));

		WINDOW *t=newwin(9,21,y/2-3,x/2-14); box(t,0,0);
		wrefresh(t); delwin(t);

		text2(6,x/2-27,a);

		for(i=0;i<y;i++)
			draw(i,0,12,b);

		for(i=0;i<x;i++)
			draw(y-1,i,3,a);	

		for(i=0;i<y;i++)
			draw(i,x-2,4,b);

		for(i=2;i<x;i++)
			draw(0,i,2,a);

		for(i=0;i<59;i++)
			draw(12,x/2-33+i,5,a);
		
		for(k=0;k<m_size1;k++)
		{
			if(k==line)
			{
				mvprintw(y/2-1+k,x/2-m_size2/2-4,"->");
				attron(COLOR_PAIR(1));
				mvprintw(y/2-1+k,x/2-m_size2/2-1,menu_[k]); 
			}
			else if(k==1&&*new_round==1)
			{
				attron(COLOR_PAIR(9));
				mvprintw(y/2-1+k,x/2-m_size2/2-1,menu_[k]); 
				attroff(COLOR_PAIR(9));
			}
			else
			{
				attroff(COLOR_PAIR(1));
				mvprintw(y/2-1+k,x/2-m_size2/2-1,menu_[k]); 
			}
		}

		mvprintw(0,0,""); c=getch();

		if(c==KEY_UP)
		{
			if(line==2&&*new_round==1)
				line=0;
			else if(line>0)
				line--;
			else	
				line=m_size1-1;
		}
		else if(c==KEY_DOWN)
		{
			if(line==0&&*new_round==1)
				line=2;
			else if(line<m_size1-1)
				line++;
			else
				line=0;
		}
		else if(c==10&&line==0)
		{
			if(*new_round==0)
			{
				map_reset(*map_no,R,argv); 
				*new_round=1;
			}

			int no_=map_selector(argc,argv,*dif,*mode);

			if(no_>0)
				match(argc,argv,new_round,map_no,dif,mode,R,no_);
		}
		else if(c==10&&line==1)
			match(argc,argv,new_round,map_no,dif,mode,R,0);
		else if(c==10&&line==2)
			s_menu_(dif,mode);
		else if(c==10&&line==3)
		{
			if(*new_round==0)
				map_reset(*map_no,R,argv); 
				
			start=0;
		}
		
		refresh();
	}
	
	delwin(a); delwin(b);

	return 0;
}
