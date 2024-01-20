#include "Tile.h"

Tile::Tile(sf::Sprite hidden, sf::Sprite revealed, sf::Sprite mine, sf::Sprite flag, 
	bool isItRevealed, bool isItFlagged, bool haveMine)
{
	this->hidden = hidden;
	this->revealed = revealed;
	this->mine = mine;
	this->flag = flag;
	this->isrevealed = isItRevealed;
	this->isflagged = isItFlagged;
	this->haveMine = haveMine;
	this->isChecked = false;
}

sf::Sprite& Tile::getMine()
{
	return mine;
}

sf::Sprite& Tile::getFlag()
{
	return flag;
}

sf::Sprite& Tile::getHidden()
{
	return hidden;
}

sf::Sprite& Tile::getRevealed()
{
	return revealed;
}

sf::Sprite& Tile::getNum()
{
	return number;
}

bool Tile::IsMine()
{
	return haveMine;
}

bool Tile::IsFlagged()
{
	return isflagged;
}

bool Tile::isRevealed()
{
	return this->isrevealed;
}

void Tile::setReveal(bool state)
{
	if (!IsFlagged())  //if not flagged change state
		this->isrevealed = state;
}

void Tile::setMine(bool state)
{
	this->haveMine = state;
}

void Tile::setFlagged(bool state)
{
	this->isflagged = state;
}

bool Tile::getChecked()
{
	return this->isChecked;
}

void Tile::setChecked(bool state)
{
	this->isChecked = state;
}

sf::Sprite Tile::makeRect(sf::Sprite& num, sf::Vector2i& position, sf::Vector2i& size)
{
	sf::IntRect numRect(position, size);
	num.setTextureRect(numRect);
	return num;
}

