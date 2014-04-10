#define MAZE_HEIGHT 7
#define MAZE_WIDTH 7
#include <stdio.h>
int visited[7][7]=
	{
		{1,0,1,1,1,1,0},
		{1,1,0,0,1,0,0},
		{0,1,1,0,1,1,0},
		{1,1,1,0,0,0,0},
		{1,1,1,0,0,1,0},
		{1,0,1,0,0,1,0},
		{1,1,1,1,1,0,0}
	};

int v_x =0;
int v_y =0;

int increment_v(){
/*
 * set v_y, v_x to new explore position.
 *
 * return 1 if everything is visited
 * return 0 if still exploring
 * 
 */
 	int vcell=0;
 	int vcell_n=0;
 	int vcell_e=0;
 	int vcell_s=0;
 	int vcell_w=0;

	while(1){
		vcell = visited[v_y][v_x];
		if(v_y < (MAZE_HEIGHT-1)) vcell_n = visited[v_y+1][v_x];
		else vcell_n = 1;

 		if(v_x < (MAZE_WIDTH-1)) vcell_e = visited[v_y][v_x+1];
 		else vcell_e =  1;

 		if(v_y>0)vcell_s = visited[v_y-1][v_x];
 		else vcell_s = 1;

 		if(v_x>0) vcell_w = visited[v_y][v_x-1];
 		else vcell_w = 1;

		if (vcell){
			if(v_x<(MAZE_WIDTH-1)){
				v_x++; //increment v_x
			}else{
				if(v_y==MAZE_HEIGHT-1){
					//TO-DO, EVERYTHING EXPLORED
					return 1;
				}else{
					v_y++;
					v_x=0;
				}
			}
		}else{
			//if every cell around it is visited, mark as visited
			if(vcell_n && vcell_e && vcell_s && vcell_w){
				visited[v_y][v_x]=1;
			}
			
			break;
		}
	}
	return 0;
}

int main(){
	int x=0;
	int y=0;

	int r=0;

	while(r!=1){
		r = increment_v(v_x, v_y);
		printf("next unvisited, (%d,%d)\n", v_x, v_y);
		visited[v_y][v_x]=1;
	}
}
