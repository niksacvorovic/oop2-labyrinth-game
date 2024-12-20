#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "PowerUp.hpp"

class GameBoard{
    int width, height, item_count;
    char** board;
    int player_x, player_y;
    int enemy_x, enemy_y;
    std::vector<PowerUp*> powerups;
    public:
    GameBoard(int dim_1, int dim_2, int count) : width(dim_1), height(dim_2), item_count(count), board(new char* [height]){
        for(int i = 0; i < height; ++i) board[i] = new char[width];
    }
    ~GameBoard();
    void generate_outer_walls();
    void generate_inner_walls();
    bool check_board();
    void set_items();
    bool path_check(std::set<std::pair<int, int>>* visited, std::pair<int, int> current);
    void generate();
    void player_move();
    void acquire_powerup();
    void activate_powerups();
    void enemy_move();
    bool game_end();
    friend std::ostream& operator<<(std::ostream& os, const GameBoard& g);
};