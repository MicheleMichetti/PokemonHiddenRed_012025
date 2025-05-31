#pragma once

#include <utils.hpp>

class Tile {
   private:
    uint8_t type_;
    uint8_t background_;
    uint8_t collision_directions_bitmask_;

   public:
    Tile();
    Tile(uint8_t type, uint8_t background, uint8_t collision_directions_bitmask);
    ~Tile();

    uint8_t getType() const;
    uint8_t getBackground() const;
    uint8_t getCollisionDirectionsBitmask() const;

    void setType(uint8_t type);
    void setBackground(uint8_t background);
    void setCollisionDirectionsBitmask(uint8_t collision_directions_bitmask);

    bool isCollision(uint8_t player_direction);
};