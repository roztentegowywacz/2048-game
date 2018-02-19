#include "game.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctype.h>

Tile::Tile() : Value(0), Blocked(false) {}

G2048::G2048() : Score(0), Total(0), FreeTiles(16) { }

void G2048::StartGame()
{
	AddTile();
	
	do
	{
		std::cout << "\033[2J";		// it is ASCII code to clear the console
		std::cout << "\033[1;1H";	// this line positions the cursor at row 1, column 1
		AddTile();
		std::cout << "Your score: "<< Total <<" (+" << Score << ")\n\n";
		DrawBoard();
		Move();
		CheckWinOrLoose();
	}
	while(true);

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
    std::cout << "+------+------+------+------+\n";
}

void G2048::AddTile()
{
	if(FreeTiles > 0)
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

		FreeTiles--;
	}
}

void G2048::MoveVertical(int x, int y, int dy)
{
	if(Board[x][y + dy].Value != 0 && Board[x][y + dy].Value == Board[x][y].Value && !Board[x][y + dy].Blocked && !Board[x][y].Blocked)
	{
		Board[x][y + dy].Value *= 2;
		Board[x][y].Value = 0;
		Board[x][y + dy].Blocked = true;
		Score = Board[x][y + dy].Value;
		Total += Score;
		FreeTiles++;
	}
	else if(Board[x][y].Value != 0 && Board[x][y + dy].Value == 0)
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
	if(Board[x + dx][y].Value != 0 && Board[x + dx][y].Value == Board[x][y].Value && !Board[x + dx][y].Blocked && !Board[x][y].Blocked)
	{
		Board[x + dx][y].Value *= 2;
		Board[x][y].Value = 0;
		Board[x + dx][y].Blocked = true;
		Score = Board[x + dx][y].Value;
		Total += Score;
		FreeTiles++;
	}
	else if(Board[x][y].Value != 0 && Board[x + dx][y].Value == 0)
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

void G2048::Move()
{
	std::cout << "\n\nPlease push one of the below button:\n";
	std::cout << "(W)Up (S)Down (A)Left (D)Right  -> (E)Exit <-\n\n";
	
	// Reset Blocked value and set the Score to 0.
	for(int x = 0; x < 4; ++x)
	{
		for(int y = 0; y < 4; ++y)
			Board[x][y].Blocked = false;
	}
	Score = 0;

	char PushButton;
	std::cin >> PushButton;
	switch(toupper(PushButton))
	{
		case 'W':
			MoveUp();
			break;
		case 'D':
			MoveRight();
			break;
		case 'S':
			MoveDown();
			break;
		case 'A':
			MoveLeft();
			break;
		case 'E':
			std::cout << "Are you shure? Please, press one of the key: y/n\n";
			char c;
			std::cin >> c;
			if(toupper(c) == 'Y')
				exit(0);
			else
				Move();
	}
}

void G2048::CheckWinOrLoose()
{
	if(FreeTiles < 1)
	{
		std::cout << "\n\nSorry, you loose the game. \n"; 
		std::cout << "Press any key to exit. \n"; 
		std::cin.get();
		exit(0);
	}
	if(Score >= 2048)
	{
		std::cout << "-------- YOU WIN! --------\n";
		// std::cout << "Would you like to continue? y/n\n";
		// char c;
		// 	std::cin >> c;
		// 	if(toupper(c) == 'Y')
		// 		return true;		
		// 	else
				exit(0);
	}
}