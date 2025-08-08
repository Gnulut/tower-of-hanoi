#include "tower_data.hpp"

tower_data::tower_data(){
    for(auto&peg:this->pegs){
        // prevent reallocation, saves cpu time
        peg.reserve(tower_data::MAX_HEIGHT);
    }
}

void tower_data::new_game(int new_size, start_or_target_position start_position, start_or_target_position target_position){
    this->size = new_size;
    this->cache_target_position = target_position;
    {// reset items
        for(int i=0; i<tower_data::MAX_WIDTH; ++i){
            pegs[i].clear();
        }
    }
    {// setup start pegs
        float_color disk_color;
        int disk_size = this->size;
        int location_horizontal = static_cast<int>(start_position);
        int location_vertical;
        std::uniform_int_distribution<> randomizer(0, tower_data::MAX_WIDTH-1); // [0, MAX_WIDTH-1], MAX_WIDTH normally=3
        for(int i=0; i<this->size; ++i, --disk_size){
            // make color, idea taken from SDL example "Clear"
            double frac =  (double) disk_size / this->size;
            disk_color.red = (float)(0.5 + 0.5 * SDL_sin(SDL_PI_D * frac));
            disk_color.green = (float)(0.5 + 0.5 * SDL_sin(SDL_PI_D * frac * 2 / 3));
            disk_color.blue = (float)(0.5 + 0.5 * SDL_sin(SDL_PI_D * frac * 4 / 3));
            disk_color.alpha = SDL_ALPHA_OPAQUE_FLOAT;

            // get horizontal position
            if(start_position == start_or_target_position::RANDOM){
                location_horizontal = randomizer(global_rng());
            }

            // get vertical position
            location_vertical = (int) this->pegs[location_horizontal].size();
            
            // set disk
            this->disks[i].set(&disk_color, disk_size, location_horizontal, location_vertical);
            this->pegs[location_horizontal].push_back(&this->disks[i]);

            // cache
            this->cache_start_disks[i] = this->disks[i];
        }
    }// endof setup start pegs
    // create target, unfortunately create and reset share the same function
    this->reset_target();
    this->compute_optimal();
}

void tower_data::reset_start(){
    for(int i=0; i<tower_data::MAX_WIDTH; ++i){
        this->pegs[i].clear();
    }
    for(int i=0; i<this->size; ++i){
        this->disks[i] = this->cache_start_disks[i];
        this->pegs[this->disks[i].get_horizontal()].push_back(&this->disks[i]);
    }
}

void tower_data::reset_target(){
    float_color disk_color;
    int disk_size = this->size;
    int location_horizontal = static_cast<int>(this->cache_target_position);
    int target_location_verticals[tower_data::MAX_WIDTH]={};
    std::uniform_int_distribution<> randomizer(0, tower_data::MAX_WIDTH-1); // [0, MAX_WIDTH-1], MAX_WIDTH normally=3
    for(int i=0; i<this->size; ++i, --disk_size){
        // get horizontal position
        if(this->cache_target_position == start_or_target_position::RANDOM){
            location_horizontal = randomizer(global_rng());
        }

        // get vertical position
        int location_vertical = target_location_verticals[location_horizontal]++;

        // set disk
        this->target_disks[i].set(&disk_color, disk_size, location_horizontal, location_vertical);
    }
}

void tower_data::move(int source_position, int destination_position) {
    // source and destination should be different from call, nevertheless we check again
    if(source_position == destination_position){
        return;
    }

    {// availability check
        // one-direction version
        // if (this->pegs[source_position].empty() || 
        //     !this->pegs[destination_position].empty() && 
        //     this->pegs[source_position].back()->get_size() > this->pegs[destination_position].back()->get_size()){
        //     return;// no disk source or too big disk
        // }

        // two-direction version
        if (this->pegs[source_position].empty() && this->pegs[destination_position].empty()){
            return;
        }
        if (this->pegs[source_position].empty() || 
            !this->pegs[destination_position].empty() && 
            this->pegs[source_position].back()->get_size() > this->pegs[destination_position].back()->get_size())
        {
            std::swap(source_position, destination_position);
        }
    }
    
    // after we check availability, we move the disk
    this->pegs[source_position].back()->move_to(destination_position, (int)this->pegs[destination_position].size());
    this->pegs[destination_position].push_back(this->pegs[source_position].back());
    this->pegs[source_position].pop_back();
}

int tower_data::get_height() const {
    return this->size;
}

const std::vector<tower_disk*>& tower_data::view_peg(int index) const {
    return this->pegs[index];
}

const tower_disk* tower_data::view_target() const {
    return this->target_disks;
}

unsigned int tower_data::get_optimal() const {
    return this->optimal_moves;
}

void tower_data::compute_optimal() {
    this->optimal_moves = 0;
    std::vector<int> current_disks(this->get_height()), target_disks(this->get_height());
    for(int i=0; i<this->get_height(); ++i){
        current_disks[i] = this->disks[i].get_horizontal();
        target_disks[i] = this->target_disks[i].get_horizontal();
    }
    this->compute_optimal_utils(current_disks, target_disks, 0);
}

void tower_data::compute_optimal_utils(std::vector<int>& current_disks, std::vector<int>& target_disks, int idx) {
    if(idx==current_disks.size())return;
    if(current_disks[idx]==target_disks[idx]){
        tower_data::compute_optimal_utils(current_disks, target_disks, idx+1);
    }else{
        bool same = true;
        for(int i=idx+2; i<current_disks.size(); ++i){
            if(current_disks[i] != current_disks[idx+1]){
                same=false;
                break;
            }
        }
        int other = 3^target_disks[idx]^current_disks[idx]; // 0+1+2=3, 0^1^2=3
        if(same){
            int count = (int) current_disks.size()-(idx+1);
            this->optimal_moves += (1<<count)-1;
            for(int i=idx+1; i<current_disks.size(); ++i){
                current_disks[i] = other;
            }
        }else{ 
            std::vector<int> new_current_disks, new_target_disks;
            for(int i=idx+1; i<current_disks.size(); ++i){
                new_current_disks.push_back(current_disks[i]);
                new_target_disks.push_back(other);
            }
            tower_data::compute_optimal_utils(new_current_disks, new_target_disks, 0);
            for(int i=idx+1,j=0; j<new_current_disks.size(); ++i, ++j){
                current_disks[i] = new_current_disks[j];
            }
        }
        current_disks[idx] = target_disks[idx];// this line could be removed
        ++this->optimal_moves;
        tower_data::compute_optimal_utils(current_disks, target_disks, idx+1);
    }
}