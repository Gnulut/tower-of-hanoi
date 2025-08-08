#pragma once

#include "color.hpp"

class tower_disk{
public:
    // set/reset values
    void set(float_color* disk_color, int disk_size, int location_horizontal, int location_vertical);

    // get preferred color of this disk
    const float_color& get_color() const;

    // get current horizontal position
    int get_horizontal() const;

    // get current height/vertical position
    int get_vertical() const;

    // get disk_size
    int get_size() const;

    // move disk to another position
    void move_to(int location_horizontal, int location_vertical);
    
private:
    // contain color, rgba format
    float_color disk_color;
    // disk size in rank, rank-1 smallest, rank-n biggest
    int disk_size;
    // horizontal location, 0-indexed
    int location_horizontal;
    // vertical location, 0-indexed, 0 represent bottom of the peg/tower
    int location_vertical;
};