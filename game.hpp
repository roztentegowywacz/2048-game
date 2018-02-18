#ifndef game_hpp
#define game_hpp

class Tile
{
public:
    Tile();
    int Value;
};
 
class G2048
{
public:
    G2048() { };
    void StartGame();
private:
    Tile Board[4][4];
    void DrawBoard();
    void AddTile();
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    void MoveVertical(int x, int y, int dy);
    void MoveHorisontal(int x, int y, int dx);
};

#endif