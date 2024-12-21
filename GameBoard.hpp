#pragma once
#include <iostream>
#include <vector>
#include <set>

class GameBoard{
    int width, height, item_count;
    char** matrix;
    public:
    inline GameBoard(int x, int y, int count) : width(x), height(y), item_count(count), matrix(new char* [height]){
        for(int i = 0; i < height; ++i) matrix[i] = new char[width];
    }
    ~GameBoard();
    void generate_outer_walls(int player_x, int player_y, int enemy_x, int enemy_y);
    void generate_inner_walls();
    bool check_board(int player_x, int player_y, int enemy_x, int enemy_y);
    void set_items();
    bool path_check(std::set<std::pair<int, int>>* visited, std::pair<int, int>& current, std::pair<int, int>& final);
    void generate(int player_x, int player_y, int enemy_x, int enemy_y);
    int get_width();
    int get_height();
    char* operator[](int index);
    friend std::ostream& operator<<(std::ostream& os, const GameBoard& g);
};