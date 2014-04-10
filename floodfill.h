#include <stdio.h>
#define MAZE_HEIGHT 7
#define MAZE_WIDTH 7
int fnum[MAZE_WIDTH][MAZE_HEIGHT]; //numbers assigned from floodfill
typedef enum { false, true } bool;
void initMaze();
bool isWallEast(int x, int y);
bool isWallWest(int x, int y);
bool isWallNorth(int x, int y);
bool isWallSouth(int x, int y);
int explore(int x, int y, int goal_x, int goal_y, int orientation, int front, int left, int right);
int mapCell(int x, int y, int orientation, int front, int left, int right);
int setWall(int x, int y, int dir);
int getFNum(int x,int y);
void setFNum(int x, int y, int num);
void floodfill(int x, int y, int level);
