#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "randomize.h"
#include "design.h"
#include "menu.h"
#include "game.h"

#define N 10
#define M 10

void map_reset(int map_no, char R[][10], char **argv)
{
	FILE *myFile=fopen(argv[map_no],"w");

	int i, j;

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		fputc(R[i][j],myFile);
	
		fputc('\n',myFile);
	}
			
	fclose(myFile); 
}

int remained(char **m)
{
	int i, j, n=0;
		
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			if(m[i][j]!='*')
				n++;

	return n;
}

int finish(char **m)
{
	int i, j;
		
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			if(m[i][j]=='#')
				return 0;			
	
	return 1;
}

void rand_(int *xx, int *yy, char **m1)
{
	int r=rand()%4;

	if(r==0&&(*xx)-1>=0&&m1[(*yy)][(*xx)-1]!='*')
		(*xx)--;
	else if(r==1&&(*xx)+1<M&&m1[(*yy)][(*xx)+1]!='*')
		(*xx)++;
	else if(r==2&&(*yy)-1>=0&&m1[(*yy)-1][(*xx)]!='*')
		(*yy)--;
	else if(r==3&&(*yy)+1<N&&m1[(*yy)+1][(*xx)]!='*')
		(*yy)++;
	else
	{
		while(m1[(*yy)][(*xx)]=='*')
		{
			(*xx)=rand()%10;
			(*yy)=rand()%10;	
		}	
	}
}

void destroy_in_advance(char **m1, char **m2, char **mask, int *no1, int *no2, int *mistakes, int *winner, int *move)
{
	int n1=remained(mask), n2=remained(m1), h=1, i;

	if(n1>10&&n2>10)
	{
		int xx1=rand()%10, yy1=rand()%10;
		int xx2=rand()%10, yy2=rand()%10;

		for(i=0;i<10;i++)
		{
			while(mask[yy1][xx1]=='*')
			{
				xx1=rand()%10;
  				yy1=rand()%10;
			}
			
			if(mask[yy1][xx1]=='#')	
				(*no1)++;
			else
				(*mistakes)--, h=2;
				
			m2[yy1][xx1]='*'; mask[yy1][xx1]='*';

			if(finish(mask)&&*winner==0)
				*winner=1;

			while(m1[yy2][xx2]=='*')
			{
				xx2=rand()%10;
				yy2=rand()%10;
			}

			if(m1[yy2][xx2]=='#')
				(*no2)++;
			else
				h=1;

			m1[yy2][xx2]='*';

			if(finish(m1)&&*winner==0)
				*winner=2;
		}
				
		mvprintw(24,3,"S-a mers in fata cu 10 pasi!");
		refresh(); sleep(3);
	}
	else
	{
		mvprintw(24,3,"Nu se poate realiza destroy in advance!");
		refresh(); sleep(3);
	}

	*move=h;
}

void randomize_map(char **m1, int **m3, char aux[][10])
{
	int ship_type1=0, ship_type2=0;
	int ship_type3=0, ship_type4=0;
	
	int i, j;

	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			if(m1[i][j]=='#')
			{
				int dir1=i, dir2=i, dir3=j, dir4=j;
				int rest1=0, rest2=0, rest3=0, rest4=0;

				while(dir1+1<N&&aux[dir1+1][j]=='#')
				{
					if(m1[dir1+1][j]=='*')
						rest1++;
					else
						m1[dir1+1][j]='0';
					
					dir1++; 
				}
				
				while(dir2-1>=0&&aux[dir2-1][j]=='#')
				{
					if(m1[dir2-1][j]=='*')
						rest2++;
					else
						m1[dir2-1][j]='0';

					 dir2--;
				}

				while(dir3+1<M&&aux[i][dir3+1]=='#')
				{
					if(m1[i][dir3+1]=='*')
						rest3++;
					else
						m1[i][dir3+1]='0';

					dir3++;
				}

				while(dir4-1>=0&&aux[i][dir4-1]=='#')	
				{
					if(m1[i][dir4-1]=='*')
						rest4++;
					else
						m1[i][dir4-1]='0';
					
				        dir4--;
				}

				int no, no1=dir1-dir2+1-rest1-rest2, no2=dir3-dir4+1-rest3-rest4;

				if(no1>no2)
					no=no1;
				else
					no=no2;

				if(no==4)
					ship_type1++;

				else if(no==3)
					ship_type2++;

				else if(no==2)
					ship_type3++;

				else if(no==1)
					ship_type4++;
			}

	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			m3[i][j]=0;

	for(i=0;i<ship_type1;i++)
		ship1_g(m3);

	for(i=0;i<ship_type2;i++)
		ship2_g(m3);
	
	for(i=0;i<ship_type3;i++)
		ship3_g(m3);
	
	for(i=0;i<ship_type4;i++)
		ship4_g(m3);

	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			if(m3[i][j])
				m1[i][j]='#';
			else
				m1[i][j]='0';

	for(i=0;i<N;i++)
		strcpy(aux[i],m1[i]);
	
	refresh();
}

void match(int argc, char **argv, int *new_round, int *map_no, int *dif, int *mode, char R[][10], int no_)
{
	int i, j, **m3, start=1, move=rand()%2+1;
	char **m1, **m2, **mask, aux[N][M];

	m1=malloc(N*sizeof(char*));
	m2=malloc(N*sizeof(char*));

	m3=malloc(N*sizeof(int*));
	mask=malloc(N*sizeof(char*));
		
	for(i=0;i<N;i++)
	{
		m1[i]=malloc(M*sizeof(char));
		m2[i]=malloc(M*sizeof(char));

		m3[i]=malloc(M*sizeof(int));
		mask[i]=malloc(M*sizeof(char));
	}

	clear(); attron(A_BOLD);
	
	if(*new_round==1)
	{
		int l=0;
		char c[15];
		
		FILE *myFile=fopen(argv[no_],"r");

		while(fgets(c,15,myFile)!=NULL)
		{
			if(l<N)
				strcpy(m1[l],c);

			l++;
		}

		for(i=0;i<N;i++)
			for(j=0;j<M;j++)
			{
				m2[i][j]='0';
				m3[i][j]=0;

				R[i][j]=m1[i][j];
			}

		generate(m3);

		for(i=0;i<N;i++)
			for(j=0;j<M;j++)
				if(m3[i][j])
					mask[i][j]='#';
				else
					mask[i][j]='0';

		fclose(myFile);
	}
	else
	{	
		int l=0;
		char c[15];
		
		FILE *myFile=fopen(argv[*map_no],"r");

		while(fgets(c,15,myFile)!=NULL)
		{
			if(l<N)
				strcpy(m1[l],c);
			else if(l<2*N)
				strcpy(mask[l-N],c);
			else if(l==2*N)
			{
				char C=c[0];
		
				*dif=C-'0';
			}
			else if(l==2*N+1)
			{
				char C=c[0];
		
				*mode=C-'0';
			}
			else
			{
				char C=c[0];
		
				move=C-'0';
			}
			

			l++;
		}

		l=0;

		for(i=0;i<N;i++)
			for(j=0;j<M;j++)
				if(mask[i][j]!='*')
					m2[i][j]='0';
				else
					m2[i][j]='*';

		fclose(myFile);
	}

	for(i=0;i<N;i++)
		strcpy(aux[i],m1[i]);

	int x1=0, y1=0, x2, y2, c;

	int no1=0, no2=0, mistakes=15, T=0, winner=0;

	WINDOW *a=newwin(1,1,0,0); box(a,0,0);
	WINDOW *b=newwin(1,2,0,0); box(b,0,0);

	while(start)
	{
		clear();

		int pos1, pos2;
		int X, Y;

		getmaxyx(stdscr,Y,X);

		text1(3,75);
		text5(15,63,a);

		mvprintw(15,85,"-> Casute doborate de tine: %d.",no1);
		mvprintw(17,85,"-> Casute doborate de computer: %d.",no2);

		if(*mode==2)
		{
			attron(COLOR_PAIR(11));
			mvprintw(21,63,"Modul try hard este pornit!");
			attroff(COLOR_PAIR(11));

			mvprintw(23,63,"Greseli ramase: %d.",mistakes);
		}

		mvprintw(Y-3,5,"- randomize map");
		mvprintw(Y-5,5,"- destroy in advance");
		mvprintw(Y-3,X-25,"Apasa   pentru a iesi");

		attron(COLOR_PAIR(11));
		mvprintw(Y-3,3,"r");
		mvprintw(Y-5,3,"d");
		mvprintw(Y-3,X-19,"q");
		attroff(COLOR_PAIR(11));

		draw(Y-9,60,2,a);
		draw(Y-7,60,3,a);
		draw(Y-5,60,6,a);
		draw(Y-3,60,4,a);

		mvprintw(Y-9,61," - casuta neincercata");
		mvprintw(Y-7,61," - casuta ce aparatine unei nave");
		mvprintw(Y-5,61," - casuta incercata");
		mvprintw(Y-3,61," - pozitie curenta");

		for(j=70;j<126;j++)
			draw(10,j,7,a);

		for(i=0;i<Y;i++)
		{
			draw(i,0,5,b);
			draw(i,X-2,5,b);
		}

		for(j=0;j<X;j++)
		{
			draw(0,j,5,a);
			draw(Y-1,j,5,a);
		}

		for(i=0;i<Y-1;i++)
			draw(i,56,5,b);

		for(j=0;j<57;j++)
			draw(22,j,5,a);

		mvprintw(2,3,"P"); mvprintw(3,3,"L"); mvprintw(4,3,"A"); 
		mvprintw(5,3,"Y"); mvprintw(6,3,"E"); mvprintw(7,3,"R");

		mvprintw(2,33,"C"); mvprintw(3,33,"O"); mvprintw(4,33,"M"); 
		mvprintw(5,33,"P"); mvprintw(6,33,"U"); mvprintw(7,33,"T");
		mvprintw(8,33,"E"); mvprintw(9,33,"R");

		pos1=2;
	
		for(i=0;i<N;i++)
		{
			pos2=5;

			for(j=0;j<M;j++)
			{
				if(m1[i][j]=='0')
					draw(pos1,pos2,2,a);
				else if(m1[i][j]=='#')
					draw(pos1,pos2,3,a);
				else 
					draw(pos1,pos2,6,a);

				pos2+=2;
			}
		
			pos1+=2;
		}

		pos1=2;
		
		for(i=0;i<N;i++)
		{
			pos2=35;
			
			for(j=0;j<M;j++)
			{
				if(move==1&&y1==i&&x1==j)
					draw(pos1,pos2,4,a);
				else if(m2[i][j]=='0')
					draw(pos1,pos2,2,a);
				else
					draw(pos1,pos2,6,a);
				
				pos2+=2;
			}

			pos1+=2;
		}
		
		if(move==1)
		{
			int xx_, yy_;
 	
			getmaxyx(stdscr,yy_,xx_);
			mvprintw(24,3,"Este randul tau.");

			c=getch();

			if(c==KEY_UP)
			{
				if(y1-1>=0)
					y1--;
				else 
					y1=N-1;
			}
			else if(c==KEY_DOWN)
			{
				if(y1+1<N)
					y1++;		
				else
					y1=0;
			}
			else if(c==KEY_LEFT)
			{
				if(x1-1>=0)
					x1--;
				else
					x1=M-1;
			}
			else if(c==KEY_RIGHT)
			{
				if(x1+1<M)
					x1++;
				else
					x1=0;
			}
			else if(c==10)
			{
				if(mask[y1][x1]=='0')
				{
					move=2; m2[y1][x1]='*'; mask[y1][x1]='*'; mistakes--; T=0;

					mvprintw(24,3,"Casuta aleasa nu apartine unei nave. :(");
					refresh(); sleep(2);
					
				}
				else if(mask[y1][x1]=='#')
				{
					m2[y1][x1]='*'; mask[y1][x1]='*'; no1++;

					mvprintw(24,3,"Felicitari, casuta apartinea unei nave! :)");
					refresh(); sleep(2);
				}
				else
				{
					mvprintw(24,3,"Aceasta casuta a fost deja aleasa!");
					refresh(); sleep(2);
				}
			}
			else if(c=='d')
				destroy_in_advance(m1,m2,mask,&no1,&no2,&mistakes,&winner,&move);

			else if(c=='r')
				randomize_map(m1,m3,aux);	

			else if(c=='q')
			{
				if(*new_round==1)
					*map_no=no_, *new_round=0;

			        start=0;

				FILE *myFile=fopen(argv[*map_no],"w");

				for(i=0;i<N;i++)
					fputs(m1[i],myFile);

				for(i=0;i<N;i++)
				{
					for(j=0;j<M;j++)
						fputc(mask[i][j],myFile);

					fputc('\n',myFile);
				}
		
				fprintf(myFile,"%d\n",*dif);
				fprintf(myFile,"%d\n",*mode);
				fprintf(myFile,"%d",move);

				fclose(myFile);
			}
			
		}
		else
		{
			int xx=rand()%10, yy=rand()%10;
			int xx_, yy_;

			if(*dif==1)
			{
				while(m1[yy][xx]=='*')
				{
					xx=rand()%10;
					yy=rand()%10;	
				}
			}
			else if(*dif==2)
			{
				while(m1[yy][xx]!='#')
				{
					xx=rand()%10;
					yy=rand()%10;	
				}
				
				rand_(&xx,&yy,m1);
			}
			else
			{
				while(m1[yy][xx]!='#')
				{
					xx=rand()%10;
					yy=rand()%10;	
				}
				
				if(T==0)
					T=1;
				else
					rand_(&xx,&yy,m1), T=rand()%2;
			}
 	
			getmaxyx(stdscr,yy_,xx_);

			mvprintw(24,3,"Computer-ul este la rand."); 
			refresh(); sleep(2);

			mvprintw(25,3,"Computer-ul a ales casuta: (%d, %d).",yy+1,xx+1);
			refresh(); sleep(2); 
			
			if(m1[yy][xx]=='0')
			{
				move=1; m1[yy][xx]='*';

				mvprintw(26,3,"Computer-ul a ales gresit!");
			}
			else if(m1[yy][xx]=='#')
			{
				m1[yy][xx]='*'; no2++;

				mvprintw(26,3,"Computer-ul a nimerit!");
			}

			refresh(); sleep(2);
		}

		if(winner==0)
		{
			if((*mode==2&&mistakes<=0)||finish(m1))
				winner=2, start=0;
			else if(finish(mask))
				winner=1, start=0;
		}
	}

	for(i=0;i<N;i++)
	{
		free(m1[i]); 
		free(m2[i]);

		free(m3[i]); 
		free(mask[i]);
	}

	free(m1); free(m2); free(m3); free(mask);
	delwin(a); delwin(b);

	int X, Y;

	getmaxyx(stdscr,Y,X); clear();
	
	if(winner==1)
		text6(Y/2-5,X/2-30), map_reset(*map_no,R,argv), refresh(), sleep(3);
	else if(winner==2)
		text7(Y/2-5,X/2-30), map_reset(*map_no,R,argv), refresh(), sleep(3);
}
