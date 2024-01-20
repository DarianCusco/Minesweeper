#pragma once
#include "TextureManager.h"
using namespace std;

class Tile
{
	sf::Sprite mine;
	sf::Sprite flag;
	sf::Sprite hidden;
	sf::Sprite revealed;
	sf::Sprite number;
	bool isrevealed;  // Is it revealed
	bool isflagged;   // Is it flagged
	bool haveMine;  // Does it have a mine
	bool isChecked;
public:
	Tile(sf::Sprite hidden, sf::Sprite revealed, sf::Sprite mine, sf::Sprite flag,
		bool isItRevealed, bool isItFlagged, bool haveMine);
	sf::Sprite& getMine();
	sf::Sprite& getFlag();
	sf::Sprite& getHidden();
	sf::Sprite& getRevealed();
	sf::Sprite& getNum();
	bool IsMine();
	bool IsFlagged();
	bool isRevealed();
	void setReveal(bool state);
	void setMine(bool state);
	void setFlagged(bool state);
	bool getChecked();
	void setChecked(bool state);
	sf::Sprite makeRect(sf::Sprite& num, sf::Vector2i& position, sf::Vector2i& size);

};

