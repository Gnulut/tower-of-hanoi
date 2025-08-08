#pragma once

#include <SDL3/SDL.h>
#include <utility>          // std::swap
#include <vector>

#include "tower_disk.hpp"
#include "random_utils.hpp"

enum class start_or_target_position{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2,
    RANDOM = 3
};

class tower_data {
private:
// unadjustable constants

    // hardcoded maximum number of tower,16 may be more reasonable, remains consideration for final version;
    static constexpr int MAX_HEIGHT = 32;
    // Tower of Hanoi generally have 3 towers maximum, this program will assume width always 3
    static constexpr int MAX_WIDTH = 3;

public:
    tower_data();
    ~tower_data() = default;

// system function(s)

    // reset tower and target tower, called when user requests new game
    void new_game(int new_size, start_or_target_position start_position, start_or_target_position target_position);

    // resets current game
    void reset_start();

    // resets/change target, only available in random
    void reset_target();

// play function(s)

    // move a topmost disk between two pegs
    void move(int source_position, int destination_position);

// misc function(s)

    // return current width, which is MAX_WIDTH
    inline static constexpr int get_width() { return tower_data::MAX_WIDTH;}

    // returns current size
    int get_height() const;

    // view peg at horizontal location, 0-based indexing
    const std::vector<tower_disk*>& view_peg(int index) const;

    // view target disks
    const tower_disk* view_target() const;

    // get optimal count
    int get_optimal() const;

    // get max height
    inline constexpr int get_max_height() const { return tower_data::MAX_HEIGHT; }
private:
// main data

    // size: how many disk in tower, size should be [1,MAX_HEIGHT] during gameplay
    int size = 0; 
    // contain disks, stored in stack instead of heap
    tower_disk disks[tower_data::MAX_HEIGHT];
    // 3 towers/pegs which hold each disk
    std::vector<tower_disk*> pegs[tower_data::MAX_WIDTH];
    // contain target disks
    tower_disk target_disks[tower_data::MAX_HEIGHT];

// cache data, used in partial reset

    // copy of start disks
    tower_disk cache_start_disks[tower_data::MAX_HEIGHT];
    start_or_target_position cache_target_position;

// functions

    // compute the optimal solution and stores it
    unsigned int optimal_moves = 0;
    void compute_optimal();

    // helper function, should only be called by compute_optimal
    void compute_optimal_utils(std::vector<int>& current_disks, std::vector<int>& target_disks, int idx);
};