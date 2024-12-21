#pragma once
#include "GameBoard.hpp"
#include "PowerUps.hpp"

class GameState{
    GameBoard board;
    PowerUp* powerups[4];
    // std::vector<PowerUp*> powerups;
    int player_x, player_y;
    int enemy_x, enemy_y;
    public:
    inline GameState(int x, int y, int count) : board(GameBoard(x, y, count))
    , player_x((std::rand() % (x - 2)) + 1), player_y(1)
    , enemy_x((std::rand() % (x - 2)) + 1), enemy_y(y - 2)
    , powerups{nullptr, nullptr, nullptr, nullptr}{
        board.generate(player_x, player_y, enemy_x, enemy_y);
    };
    ~GameState();
    void acquire_powerup();
    bool activate_powerup(int index, int x, int y);
    void decay_powerups();
    void print_board();
    void player_move();
    void enemy_move();
    bool game_end();
};