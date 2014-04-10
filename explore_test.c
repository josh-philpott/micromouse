#ifndef FLOODFILL_H
#define FLOODFILL_H
#include "floodfill.h"
#endif
#include <stdio.h>

int walls_real[7][7] = //0-no walls, 1-north wall, 2-east wall 3- north and east wall
	/*{{2,1,1,1,1,0,0},
     {1,1,1,0,3,0,0},
	 {1,1,1,3,0,0,0},
	 {0,0,0,0,0,0,0},
	 {0,0,0,0,0,0,0},
	 {0,0,0,0,0,0,0},
	 {0,0,0,0,0,0,0}};*/
	/*{{2,0,2,2,0,0,3},
     {2,3,2,2,3,0,2},
	 {2,2,0,1,3,1,2},
	 {1,0,2,0,1,0,2},
	 {0,2,0,2,1,2,3},
	 {1,2,1,3,0,0,2},
	 {1,1,3,1,1,1,3}};
	{{3,1,1,3,1,1,3},
     {0,1,1,2,2,2,2},
	 {2,3,1,3,2,2,2},
	 {2,0,3,0,1,2,2},
	 {0,3,2,2,2,1,2},
	 {2,2,2,0,1,1,3},
	 {2,0,0,1,1,1,2}};*/

	/*{{2,0,0,1,1,1,2},
	 {2,2,2,0,1,1,3},
	 {0,3,2,2,2,1,2},
	 {2,0,3,0,1,2,2},
	 {2,3,1,3,2,2,2},
	 {0,1,1,2,2,2,2},
	 {3,1,1,3,1,1,3}};*/

	/*{{2,2,2,2,1,0,2},
	 {0,1,0,0,1,0,2},
	 {2,2,2,1,2,3,3},
	 {0,1,3,0,1,3,2},
	 {0,2,0,2,1,1,2},
	 {1,2,1,2,2,1,2},
	 {1,1,1,1,1,1,3}};*/

	 
/*	 
   {{2,1,2,0,0,0,3},
	{0,0,2,2,3,0,3},
	{2,3,0,3,2,1,2},
	{2,0,0,0,0,0,2},
	{2,3,3,1,3,1,3},
	{2,0,2,2,0,0,2},
	{1,1,1,1,1,3,3}};*/

   {{2,1,2,1,0,0,2},
	{0,1,0,0,1,2,3},
	{2,0,2,1,3,1,2},
	{2,0,2,0,0,2,2},
	{2,0,2,2,0,0,3},
	{2,3,1,3,3,2,2},
	{1,1,1,1,3,1,3}};


void addToWalls( int x, int y, int orient, int * front, int * left, int * right){
	const int WALL = 100;
	*left = 0;
	*right = 0;
	*front = 0;

	int cell = walls_real[y][x];
	int cell_west=0;
	int cell_east=0;
	int cell_north=0;
	int cell_south=0;
	

	if(x<(MAZE_WIDTH-1))cell_east = walls_real[y][x+1];
	if(y<(MAZE_HEIGHT-1))cell_north = walls_real[y+1][x];
	if(x>0)cell_west = walls_real[y][x-1];
	if(y>0)cell_south = walls_real[y-1][x];

	switch(orient){
		case 0:
			if(cell_west==2 || cell_west==3)*left=WALL;
			if(cell==1 || cell==3)*front=WALL;
			if(cell==2 || cell==3)*right=WALL;

			if(x==0)*left=WALL;
			if(x==MAZE_WIDTH-1)*right=WALL;
			if(y==MAZE_HEIGHT-1)*front=WALL;
			break;
		case 1:
			if(cell==2 || cell==3) *front = WALL;
			if(cell==1 || cell==3) *left  = WALL;
			if(cell_south==1 || cell_south==3)*right=WALL;

			if(x==MAZE_WIDTH-1)*front=WALL;
			if(y==MAZE_HEIGHT-1)*left=WALL;
			if(y==0)*right=WALL;
			break;
		case 2:
			if(cell_south==1 || cell_south==3)*front = WALL;
			if(cell_west ==2 || cell_west==3){
				*right=WALL;
			}
			if(cell==2 || cell==3)*left=WALL;

			if(y==0)*front=WALL;
			if(x==0)*right=WALL;
			if(x==MAZE_WIDTH-1)*left=WALL;
			break;
		case 3:
			if(cell_west==2 || cell_west==3)*front=WALL;
			if(cell_south==1 || cell_south==3)*left=WALL;
			if(cell==1 || cell==3)*right=WALL;

			if(x==0)*front=WALL;
			if(y==0)*left =WALL;
			if(y==MAZE_HEIGHT-1)*right=WALL;
			break;
	}

}


int main(){
	int x=0;
	int y=0;

	int orient=0; //north orientation.

	int left=0;
	int right=0;
	int front=0;

	int dir_next=0;

	int flag= 0;

	initMaze();


	while(1){
		flag++;
		if(flag>1000)break;
		addToWalls(x,y,orient,&front, &left, &right);
		orient=explore(x,y,4,4,orient,front,left,right);
		//printMaze();
		//printMaze();
		/*printFMaze();
		printVMaze();*/
		if(orient==4){
			printf("finished in %d moves.\n", flag);
			break;
		}
		if(orient==-1){
			printf("ERROR\n");break;
		}
		switch(orient){
			case 0:y++;break;
			case 1:x++;break;
			case 2:y--;break;
			case 3:x--;break;
		}
		printf("x-->%d, y-->%d, orient-->%d\n", x, y, orient);
	}
}




