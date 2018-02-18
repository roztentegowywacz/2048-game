#include "game.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>

Tile::Tile() : Value(0) {}

void G2048::StartGame()
{
	AddTile();
	AddTile();
	AddTile();
	AddTile();
	AddTile();
	DrawBoard();
	MoveUp();
	DrawBoard();
	MoveRight();
	DrawBoard();
	MoveDown();
	DrawBoard();
	MoveLeft();
	DrawBoard();

}

void G2048::DrawBoard()
{
    for(int y = 0; y < 4; ++y)
    {
	   	std::cout << "+------+------+------+------+\n"; 
	   	std::cout << "| ";
	   	for(int x = 0; x < 4; ++x)
	   	{
		    if(Board[x][y].Value == 0)
	    	    std::cout << std::setw(4) << ' ';
            else
                std::cout << std::setw(4) << Board[x][y].Value;
            std::cout << " | ";
	    }
	    std::cout << '\n';
	}
    std::cout << "+------+------+------+------+\n\n";
}

void G2048::AddTile()
{
    int x, y;
    do
    {
        x = rand() % 4;
        y = rand() % 4;
    }
    while(Board[x][y].Value != 0);
        
    int RandomValue = rand() % 100;
    if(RandomValue > 89)
        Board[x][y].Value = 4;
    else
        Board[x][y].Value = 2;
}

void G2048::MoveVertical(int x, int y, int dy)
{
	if(Board[x][y].Value != 0 && Board[x][y + dy].Value == 0)
	{
		Board[x][y + dy].Value = Board[x][y].Value;
		Board[x][y].Value = 0;
	}
	if(dy > 0) 
	{
		if(y + dy < 3)
			MoveVertical(x, y + dy, 1);
	}
	else
	{
		if(y + dy > 0)
			MoveVertical(x, y + dy, -1);
	}
}

void G2048::MoveHorisontal(int x, int y, int dx)
{
	if(Board[x][y].Value != 0 && Board[x + dx][y].Value == 0)
	{
		Board[x + dx][y].Value = Board[x][y].Value;
		Board[x][y].Value = 0;
	}
	if(dx > 0)
	{
		if(x + dx < 3)
			MoveHorisontal(x + dx, y, 1);
	}
	else
	{
		if(x + dx > 0)
			MoveHorisontal(x + dx, y, -1);
	}
}

void G2048::MoveUp()
{
	for(int x = 0; x < 4; ++x)
	{
		for(int y = 1; y < 4; ++y)
		{
			if(Board[x][y].Value)
				MoveVertical(x, y, -1);
		}
	}
}

void G2048::MoveDown()
{
	for(int x = 0; x < 4; ++x)
	{
		for(int y = 2; y >= 0; --y)
		{
			if(Board[x][y].Value)
				MoveVertical(x, y, 1);
		}
	}
}

void G2048::MoveLeft()
{
	for(int y = 0; y < 4; ++y)
	{
		for(int x = 1; x < 4; ++x)
		{
			if(Board[x][y].Value)
				MoveHorisontal(x, y, -1);
		}
	}
}

void G2048::MoveRight()
{
	for(int y = 0; y < 4; ++y)
	{
		for(int x = 2; x >= 0; --x)
		{
			if(Board[x][y].Value)
				MoveHorisontal(x, y, 1);
		}
	}
}