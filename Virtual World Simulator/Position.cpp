#include "Position.h"

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Position::getX() const
{
	return x;
}

int Position::getY() const
{
	return y;
}

void Position::setX(int x)
{
	this->x = x;
}

void Position::setY(int y)
{
	this->y = y;
}

Position Position::operator+(const Position& pos) const
{
	Position new_position(x + pos.x, y + pos.y);
	return new_position;
}

Position Position::operator-(const Position& pos) const
{
	Position new_position(x - pos.x, y - pos.y);
	return new_position;
}

bool Position::operator==(const Position& pos) const
{
	return (pos.x == x && pos.y == y);
}