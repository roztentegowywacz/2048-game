#ifndef game_hpp
#define game_hpp

class Tile
{
public:
    Tile();
    int Value;
    bool Blocked;
};
 
class G2048
{
    int Score;
    int Total;
    int FreeTiles;

public:
    G2048();
    void StartGame();
private:
    Tile Board[4][4];
    void DrawBoard();
    void AddTile();
    void Move();
    void CheckWinOrLoose();
    void MoveUp();
    void MoveRight();
    void MoveDown();
    void MoveLeft();
    void MoveVertical(int x, int y, int dy);
    void MoveHorisontal(int x, int y, int dx);
};

#endif