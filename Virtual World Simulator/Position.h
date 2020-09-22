#pragma once
class Position
{
private:
	int x;
	int y;
public:
	Position(int x = 0, int y = 0);
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	Position operator+(const Position& pos) const;
	Position operator-(const Position& pos) const;
	bool operator==(const Position& pos) const;
};

