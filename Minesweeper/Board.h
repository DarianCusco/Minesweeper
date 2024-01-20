#pragma once
#include "Tile.h"
#include <vector>

using namespace std;
class Board
{
	int width;
	int height;
	int minecount;
	int tilecount;

public:

	Board();
	Board(int width, int height, int minecount);
	int getWidth();
	int getHeight();
	int getMineCount();
	int getTileCount();
	void lowerMineCount();
	int minesNearby(vector<vector<Tile>>& tiles, int x, int y);
	void tileReveal(vector<vector<Tile>>& tiles, int x, int y);
	void setMineCount(int mine);
	void loadTestBoard(string name, vector<vector<Tile>>& tiles);
};

