#pragma once
#include <iostream>

class GameBoard{
    int width, height, item_count;
    char** board;
    int player_x, player_y;
    int enemy_x, enemy_y;
    public:
    GameBoard(int dim_1, int dim_2, int count) : width(dim_1), height(dim_2), item_count(count){}
    ~GameBoard();
    void initialize();
    void player_move();
    void enemy_move();
    bool game_end();
    friend std::ostream& operator<<(std::ostream& os, const GameBoard& g);
};