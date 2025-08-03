#include "tower_disk.hpp"

void tower_disk::set(float_color* disk_color, int disk_size, int location_horizontal, int location_vertical) {
    this->disk_color = *disk_color;
    this->disk_size = disk_size;
    this->location_horizontal = location_horizontal;
    this->location_vertical = location_vertical;
}

const float_color& tower_disk::get_color() const {
    return this->disk_color;
}

int tower_disk::get_horizontal() const {
    return this->location_horizontal;
}

int tower_disk::get_vertical() const {
    return this->location_vertical;
}

int tower_disk::get_size() const {
    return this->disk_size;
}

void tower_disk::move_to(int location_horizontal, int location_vertical){
    this->location_horizontal = location_horizontal;
    this->location_vertical = location_vertical;
}