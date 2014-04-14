//#include "numstack.h"
#ifndef FLOODFILL_H
#define FLOODFILL_H
#include "floodfill.h"
#endif
int walls[MAZE_WIDTH][MAZE_HEIGHT] = {{0}};
int visited[MAZE_WIDTH][MAZE_HEIGHT] = {{0}};
int v_x = 0;
int v_y = 0;
int rolling_flag=0;


void initMaze(){
	int i, j = 0;
	for(i=0;i<MAZE_WIDTH;i++){
		for(j=0;j<MAZE_HEIGHT; j++){
			fnum[i][j]=(MAZE_HEIGHT*MAZE_WIDTH)+1;
		}
	}
}

void printFMaze(){
	printf("\n\n");
	int i = 0;
	int j = 0;
	//printf("\n\n");
	for(i=MAZE_HEIGHT-1; i>=0; i--){
		for(j=0; j<MAZE_WIDTH; j++){
			printf(" %2d ", fnum[i][j]);
		}
			printf("\n");
	}

}

void printVMaze(){
	printf("\n\n");
	int i = 0;
	int j = 0;
	//printf("\n\n");
	for(i=MAZE_HEIGHT-1; i>=0; i--){
		for(j=0; j<MAZE_WIDTH; j++){
			printf(" %2d ", visited[i][j]);
		}
			printf("\n");
	}

	printf("v_x-->%d, v_y-->%d\n", v_x, v_y);

}

void printMaze(){
	printf("\n");
	int i = 0;
	int j = 0;
	//printf("\n\n");
	for(i=MAZE_HEIGHT-1; i>=0; i--){
		for(j=0; j<MAZE_WIDTH; j++){
			printf(" %2d ", walls[i][j]);
		}
			printf("\n");
	}
	printFMaze();
	printf("\n");
	printVMaze();
	printf("\n");
}



bool isWallWest(int x, int y){
	if(x==0){
		return true;
	}
	else if(walls[y][x-1]==2 || walls[y][x-1]==3){
		return true;
	}
	else return false;
}

bool isWallEast(int x, int y){
	if(x==MAZE_WIDTH-1){
		return true;
	}
	else if(walls[y][x]==2 || walls[y][x]==3){
		return true;
	}
	else return false;
}

bool isWallNorth(int x, int y){
	if(y==MAZE_HEIGHT-1){
		return true;
	}
	else if(walls[y][x]==1 || walls[y][x]==3){
		return true;
	}
	else return false;
}

bool isWallSouth(int x, int y){
	if(y==0){
		return true;
	}
	else if(walls[y-1][x]==1 || walls[y-1][x]==3){
		return true;
	}
	else return false;
}

int increment_v(int x, int y){
/*
 * set v_y, v_x to new explore position.
 *
 * return 1 if everything is visited
 * return 0 if still exploring
 * 
 */
	//Find next v with lowest floodnumber
	int vcell=0;
	int vcell_n=0;
	int vcell_e=0;
	int vcell_s=0;
	int vcell_w=0;
	int i = 0;
	int j = 0;
	static int count=0;
	int flag = 0;
	int low_x = 0;
	int low_y = 0;
	int low_f = (MAZE_HEIGHT*MAZE_WIDTH)+1;

 	initMaze();

 	floodfill(x,y,0);
 		

 	for(i=0;i<MAZE_WIDTH;i++){
 		for(j=0;j<MAZE_HEIGHT;j++){

 			//j will be x,
 			//i will be y
 			vcell = visited[i][j];
			if(i < (MAZE_HEIGHT-1)) vcell_n = visited[i+1][j];
			else vcell_n = 1;

	 		if(j < (MAZE_WIDTH-1)) vcell_e = visited[i][j+1];
	 		else vcell_e =  1;

	 		if(i>0)vcell_s = visited[i-1][j];
	 		else vcell_s = 1;

	 		if(j>0) vcell_w = visited[i][j-1];
	 		else vcell_w = 1;

	 		if(vcell_n && vcell_e && vcell_s && vcell_w && !vcell){
	 			printf("autoset visited at (%d,%d)\n", j,i);
	 			visited[i][j]=1;
	 			vcell = 1;
	 		}


 			if(!vcell){
 				flag = 1;
 				if(getFNum(j,i)<low_f){
 					low_f = getFNum(j,i);
 					low_x = j;
 					low_y = i;
 				}
 			}
 		}
 	}

 	if(flag){
 		v_x = low_x;
 		v_y = low_y;
 		return 0;
 	}else{
 		return 1;
 	}
}



int explore(int x, int y, int goal_x, int goal_y, int orientation, int front, int left, int right){
	/*********************************************
	*explore
	*
	*returns 
	*	-1 		- error
	*	0 - 3 	- direction (N,E,W,S)
	*	4 		- maze complete
	*
	* *******************************************/
	int cell_f_num = (MAZE_HEIGHT*MAZE_WIDTH)+1;
	int temp = (MAZE_HEIGHT*MAZE_WIDTH)+1;
	int f_num_dif = (MAZE_HEIGHT*MAZE_WIDTH)+1;
	int dir = -1;
	static int found_goal=0;
	static int maze_explore_complete=0;
	static int maze_return_start=0;
	if(!maze_explore_complete)mapCell(x, y, orientation, front, left, right); //update wall array with new view;

	visited[y][x] = 1;

	if (x==4 && y==4)found_goal=1;

	if(found_goal){
		if(increment_v(x,y) && !maze_explore_complete){
			maze_explore_complete=1;
			printf("Explore Complete! Heading back to start...\n");
		}
		goal_x = v_x;
		goal_y = v_y;
	}

	if(maze_explore_complete){
		if(x==0 && y==0){
			printf("back at start! Heading to finish...\n");
			maze_return_start=1;
		}else{
			goal_x=0;
			goal_y=0;
		}
	}

	if(maze_return_start){
			if(x==4 && y==4)return 4;
			rolling_flag=1;
			goal_x=4;
			goal_y=4;
		}

	
	initMaze();
	floodfill(goal_x,goal_y,0);
	cell_f_num = getFNum(x,y);

	if(!isWallNorth(x,y)){
		dir=0; //default to north
		if((cell_f_num - getFNum(x,y+1))>=0)f_num_dif = cell_f_num - getFNum(x,y+1);
	}
	temp = cell_f_num - getFNum(x+1, y);
	if(!isWallEast(x,y)&& (temp<f_num_dif) && temp>=0){	//if no wall east and the num is lower, go east
		dir = 1;
		f_num_dif= temp;
	}
	temp = cell_f_num - getFNum(x, y-1);
	if(!isWallSouth(x,y) && temp<f_num_dif && temp>=0){	//if no wall east and the num is lower, go east
		f_num_dif = temp;
		dir = 2;
	}

	temp = cell_f_num - getFNum(x-1, y);
	if(!isWallWest(x,y)&& temp<f_num_dif && temp>=0){	//if no wall east and the num is lower, go east
		f_num_dif = temp;
		dir = 3;
	}


	if (dir>=0){
		return dir;

	}else{
		//error. nowhere to go...
		return -1;
	}

}

int mapCell(int x, int y, int orientation, int front, int left, int right){ //0-N, 1-E, 2-S, 3-W
	int l_wall=0;
	int f_wall=0;
	int r_wall=0;

	/*Get Walls. If wall exists, set l_wall, f_wall, r_wall
	*
	*******************************************************/

	//y, Output_left, Output_right are global variables 
	if(front>55){
		f_wall = 1;
	}

	if(left>60){
		l_wall = 1;
	}

	if(right>60){
		r_wall = 1;
	}

	switch(orientation){
		case 0:	//facing north
			if (l_wall)setWall(x,y,3);
			if (r_wall)setWall(x,y,1);
			if (f_wall)setWall(x,y,0);
			break;
		case 1:
			if (l_wall)setWall(x,y,0);
			if (r_wall)setWall(x,y,2);
			if (f_wall)setWall(x,y,1);
			break;
		case 2:
			if (l_wall)setWall(x,y,1);
			if (r_wall)setWall(x,y,3);
			if (f_wall)setWall(x,y,2);
			break;
		case 3:
			if (l_wall)setWall(x,y,2);
			if (r_wall)setWall(x,y,0);
			if (f_wall)setWall(x,y,3);
			break;
	}
}


int setWall(int x, int y, int dir){ //0-N, 1-E, 2-S, 3-W
	int in_bounds = 0;
	if(dir==0 && y<(MAZE_HEIGHT-1))in_bounds=1;
	if(dir==1 && x<(MAZE_WIDTH-1))in_bounds=1;
	if(dir==2 && y>0)in_bounds=1;
	if(dir==3 && x>0)in_bounds=1;

	if(in_bounds){
		if (dir==0){		//NORTH
			if(isWallEast(x,y))walls[y][x]=3;
			else walls[y][x]=1;

		}else if(dir==1){	//EAST
			if(isWallNorth(x,y))walls[y][x]=3;
			else walls[y][x]=2;
		}else if(dir==2){	//SOUTH
			if(isWallEast(x,y-1))walls[y-1][x]=3;
			else walls[y-1][x]=1;

		}else if(dir==3){	//WEST
			if(isWallNorth(x-1,y))walls[y][x-1]=3;
			else walls[y][x-1]=2;

		}
	}
}

// To keep consistency with maze
int getFNum(int x, int y){
/*helper function to keep consistency with wall array*/

	if(x<MAZE_WIDTH && y<MAZE_HEIGHT)return fnum[y][x];
	else return -1;
}

void setFNum(int x, int y, int num){
/*helper function to keep consistency with wall array*/
	fnum[y][x]=num;
}


void floodfill(int x, int y, int level){
/*recursive function which outputs to FNum array the minimum 
number of steps required to get to the goal from each cell. Takes
into account current state of wall array.

when calling function, level should be 0

inputs: goal x position 
		goal y position
		current level (0 for first run)
returns: void

 */
	setFNum(x,y,level);
	//if no (NORTH/SOUTH/EAST/WEST) wall and the floodfill number of that cell
	//is < the current level + 1, run floodfill on the cell.
	if(!isWallNorth(x,y) && ((level+1)< getFNum(x, y+1))){
		floodfill(x,y+1,level+1);
	}
	if(!isWallEast(x,y) && ((level+1)< getFNum(x+1, y))){
		floodfill(x+1,y,level+1);
	}
	if(!isWallSouth(x,y) && ((level+1)< getFNum(x, y-1))){
		floodfill(x,y-1,level+1);
	}
	if(!isWallWest(x,y) && ((level+1)< getFNum(x-1, y))){
		floodfill(x-1,y,level+1);
	}
	return;
}

