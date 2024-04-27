#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 3
#define COLS 4

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// Rules:
// can go left, right, up, down
// start in top left, end in bottom right
// every number you cross over adds to the counter
// must equal the ending value

int Engine(int grid[ROWS][COLS], int endVal);

typedef struct 
{
	int x;
	int y;
} coord;

coord getPoint(int x, int y)
{
	coord point;
	point.x = x;
	point.y = y;
	return point;
}

int main()
{
	int grid[ROWS][COLS] = {
		{2, 5, 8, 6},
		{6, 6, 4, 3},
		{3, 6, 1, 6}
	};
	int endVal = 50;
	
	coord curPoint = getPoint(0, 0);

	switch ( Engine(grid, endVal) ) {
		case UP:
			break;
		case DOWN:
			break;
		case LEFT:
			break;
		case RIGHT:
			break;
		case -1:
			return -1;
	}

	return 0;
}

// Returns:
// 1 -> UP
// 2 -> DOWN
// 3 -> LEFT
// 4 -> RIGHT
int Engine(int grid[ROWS][COLS], int endVal)
{
	
	return -1;
}
