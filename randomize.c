#include <stdio.h>
#include <stdlib.h>
#include "randomize.h"

#define N 10
#define M 10

int valid(int x, int y, int **c)
{
	if(c[x][y])
		return 0;

	if(x-1>=0&&c[x-1][y])
		return 0;

	if(x-1>=0&&y+1<M&&c[x-1][y+1])
		return 0;

	if(y+1<M&&c[x][y+1])
		return 0;

	if(x+1<N&&y+1<M&&c[x+1][y+1])
		return 0;

	if(x+1<N&&c[x+1][y])
		return 0;

	if(x+1<N&&y-1>=0&&c[x+1][y-1])
		return 0;

	if(y-1>=0&&c[x][y-1])
		return 0;

	if(x-1>=0&&y-1>=0&&c[x-1][y-1])
		return 0;

	return 1;
}

void ship1_g(int **c)
{
	int x=rand()%10, y=rand()%10, d=rand()%2;

	c[x][y]=1;

	if(!d)
	{
		if(x-1>=0&&x+1<N)
			c[x-1][y]=c[x+1][y]=1;

		else if(x-2>=0)
			c[x-2][y]=c[x-1][y]=1;

		else if(x+2<N)
			c[x+1][y]=c[x+2][y]=1;


		if(x-2>=0&&!c[x-2][y])
			c[x-2][y]=1;

		else if(x+2<N&&!c[x+2][y])
			c[x+2][y]=1;	

		else if(x-3>=0&&!c[x-3][y])
			c[x-3][y]=1;
		
		else if(x+3<N&&!c[x+3][y])
			c[x+3][y]=1;
	}
	else
	{
		if(y-1>=0&&y+1<M)
			c[x][y-1]=c[x][y+1]=1;

		else if(y-2>=0)
			c[x][y-2]=c[x][y-1]=1;

		else if(y+2<M)
			c[x][y+1]=c[x][y+2]=1;


		if(y-2>=0&&!c[x][y-2])
			c[x][y-2]=1;

		else if(y+2<M&&!c[x][y+2])
			c[x][y+2]=1;	

		else if(y-3>=0&&!c[x][y-3])
			c[x][y-3]=1;
		
		else if(y+3<M&&!c[x][y+3])
			c[x][y+3]=1;
	}
}

void ship2_g(int **c)
{
	int x=rand()%10, y=rand()%10, ok=0;

	while(!valid(x,y,c))
		x=rand()%10, y=rand()%10;

	if(x-1>=0&&valid(x-1,y,c)&&!ok)
	{
		if(x-2>=0&&valid(x-2,y,c))
			c[x-2][y]=1, c[x][y]=1, c[x-1][y]=1, ok=1;

		else if(x+1<N&&valid(x+1,y,c))
			c[x+1][y]=1, c[x][y]=1, c[x-1][y]=1, ok=1;
	}

        if(x+1<N&&valid(x+1,y,c)&&!ok)
	{
		if(x-1>=0&&valid(x-1,y,c))
			c[x-1][y]=1, c[x][y]=1, c[x+1][y]=1, ok=1;

		else if(x+2<N&&valid(x+2,y,c))
			c[x+2][y]=1, c[x][y]=1, c[x+1][y]=1, ok=1;
	}

	if(y-1>=0&&valid(x,y-1,c)&&!ok)
	{
		if(y-2>=0&&valid(x,y-2,c))
			c[x][y-2]=1, c[x][y]=1, c[x][y-1]=1, ok=1;

		else if(y+1<N&&valid(x,y+1,c))
			c[x][y+1]=1, c[x][y]=1, c[x][y-1]=1, ok=1;
	}

	if(y+1<M&&valid(x,y+1,c)&&!ok)
	{
		if(y-1>=0&&valid(x,y-1,c))
			c[x][y-1]=1, c[x][y]=1, c[x][y+1]=1, ok=1;

		else if(y+2<M&&valid(x,y+2,c))
			c[x][y+2]=1, c[x][y]=1, c[x][y+1]=1, ok=1;
	}

	if(!ok)
		ship2_g(c);	
}

void ship3_g(int **c)
{
	int x=rand()%10, y=rand()%10;

	while(!valid(x,y,c))
		x=rand()%10, y=rand()%10;

	if(x-1>=0&&valid(x-1,y,c))
		c[x-1][y]=c[x][y]=1;

	else if(x+1<N&&valid(x+1,y,c))
		c[x+1][y]=c[x][y]=1;

	else if(y-1>=0&&valid(x,y-1,c))
		c[x][y-1]=c[x][y]=1;

	else if(y+1<M&&valid(x,y+1,c))
		c[x][y+1]=c[x][y]=1;

	else 
		ship3_g(c);
}

void ship4_g(int **c)
{
	int x=rand()%10, y=rand()%10;

	while(!valid(x,y,c))
		x=rand()%10, y=rand()%10;

	c[x][y]=1;
}

void generate(int **c)
{
	ship1_g(c);

	ship2_g(c);
	ship2_g(c);

	ship3_g(c);
	ship3_g(c);
	ship3_g(c);

	ship4_g(c);
	ship4_g(c);
	ship4_g(c);
	ship4_g(c);
}
