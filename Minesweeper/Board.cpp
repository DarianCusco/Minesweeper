#include "Board.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
using namespace std;

Board::Board()
{
	this->width = 0;
	this->height = 0;
	this->minecount = 0;
	this->tilecount = 0;
}

Board::Board(int width, int height, int minecount)
{
	this->width = width;
	this->height = height;
	this->minecount = minecount;
	this->tilecount = (height * width) - minecount;
}

int Board::getWidth()
{
	return this->width;
}

int Board::getHeight()
{
	return this->height;
}

int Board::getMineCount()
{
	return this->minecount;
}

int Board::getTileCount()
{
	return this->tilecount;
}

void Board::lowerMineCount()
{
	this->minecount -= 1;
}

int Board::minesNearby(vector<vector<Tile>>& tiles, int x, int y)
{
	// [y][x]
	// y = height
	// x = width
	int minesNear = 0;
	if (x > 0)
	{
		if (tiles[x - 1][y].IsMine()) //checks left
			minesNear++;
		if (y != height - 1)
		{
			if (tiles[x - 1 ][y + 1].IsMine()) //checks bottom left corner
				minesNear++;
		}
		if (y > 0)
		{
			if (tiles[x - 1][y - 1].IsMine()) //checks top left corner 
				minesNear++;
		}
	}
	if (y > 0)
	{
		if (tiles[x][y - 1].IsMine()) //checks above
			minesNear++;
		if (x != width - 1)
		{
			if (tiles[x + 1][y - 1].IsMine()) //checks top right corner 
				minesNear++;
		}
	}
	if (x != width - 1)
	{
		if (tiles[x + 1][y].IsMine()) //checks right
			minesNear++;
		if (y != height - 1)
		{
			if (tiles[x + 1][y + 1].IsMine()) //checks bottom right
				minesNear++;
		}
	}
	if (y != height - 1)
	{
		if (tiles[x][y + 1].IsMine()) //checks bottom
			minesNear++;
	}
	return minesNear;
}

void Board::tileReveal(vector<vector<Tile>>& tiles, int x, int y)
{
	int minesClose = minesNearby(tiles, x, y);

	if (!tiles[x][y].isRevealed() && !tiles[x][y].IsFlagged())  //If tile is not revealed or flagged
	{
		tiles[x][y].setReveal(true);
		tiles[x][y].setChecked(true);
		tilecount--;
	}

		if (minesClose == 0)
		{
			if (x > 0)
			{
				if (!tiles[x - 1][y].getChecked())
				{
					if (!tiles[x - 1][y].IsMine()) //checks left
					{
						if (!tiles[x - 1][y].isRevealed())
							tileReveal(tiles, x - 1, y);
					}
				}
				if (y != height - 1)
				{
					if (!tiles[x - 1][y + 1].getChecked())
					{
						if (!tiles[x - 1][y + 1].IsMine()) //checks bottom left corner
						{
							if (!tiles[x - 1][y + 1].isRevealed())
								tileReveal(tiles, x - 1, y + 1);
						}
					}
				}
				if (y > 0)
				{
					if (!tiles[x - 1][y - 1].getChecked())
					{
						if (!tiles[x - 1][y - 1].IsMine()) //checks top left corner 
						{
							if (!tiles[x - 1][y - 1].isRevealed())
								tileReveal(tiles, x - 1, y - 1);
						}
					}
				}
			}
			if (y > 0)
			{
				if (!tiles[x][y - 1].getChecked())
				{
					if (!tiles[x][y - 1].IsMine()) //checks above
					{
						if (!tiles[x][y - 1].isRevealed())
							tileReveal(tiles, x, y - 1);
					}
				}

				if (x != width - 1)
				{
					if (!tiles[x + 1][y - 1].getChecked())
					{
						if (!tiles[x + 1][y - 1].IsMine()) //checks top right corner 
						{
							if (!tiles[x + 1][y - 1].isRevealed())
								tileReveal(tiles, x + 1, y - 1);
						}
					}
				}
			}
			if (x != width - 1)
			{
				if (!tiles[x + 1][y].getChecked())
				{
					if (!tiles[x + 1][y].IsMine()) //checks right
					{
						if (!tiles[x + 1][y].isRevealed())
							tileReveal(tiles, x + 1, y);
					}
				}

				if (y != height - 1)
				{
					if (!tiles[x + 1][y + 1].getChecked())
					{
						if (!tiles[x + 1][y + 1].IsMine()) //checks bottom right
						{
							if (!tiles[x + 1][y + 1].isRevealed())
								tileReveal(tiles, x + 1, y + 1);
						}
					}
				}
			}
			if (y != height - 1)
			{  
				if (!tiles[x][y + 1].getChecked())
				{
					if (!tiles[x][y + 1].IsMine()) //checks bottom
					{
						if (!tiles[x][y + 1].isRevealed())
							tileReveal(tiles, x, y + 1);
					}
				}
			}
		}
	}

	void Board::setMineCount(int mine)
	{
		this->minecount = mine;
		this->tilecount = (height * width) - minecount;
	}

	void Board::loadTestBoard(string name, vector<vector<Tile>>& tiles)
	{
			fstream file(name);
			char temp;
			int character;
			int numMines = 0;

			if (file.is_open())
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						file >> temp;

						if (temp == '1')
						{
							numMines++;
							tiles[j][i].setMine(true);
						}
						else
						{
							tiles[j][i].setMine(false);
						}
						tiles[j][i].setReveal(false);
						tiles[j][i].setFlagged(false);
					}
				}
				int newMineCount = numMines;
				setMineCount(newMineCount);
			}
	}
