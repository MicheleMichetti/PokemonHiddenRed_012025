#include <Tile.hpp>
#include <utils.hpp>

Tile::Tile() {
    this->type_ = 0;
    this->background_ = 0;
    this->collision_directions_bitmask_ = 0;
}

Tile::Tile(uint8_t type, uint8_t background, uint8_t collision_directions_bitmask) {
    this->type_ = type;
    this->background_ = background;
    this->collision_directions_bitmask_ = collision_directions_bitmask;
}

Tile::~Tile() {}

uint8_t Tile::getType() const { return this->type_; }
uint8_t Tile::getBackground() const { return this->background_; }
uint8_t Tile::getCollisionDirectionsBitmask() const { return this->collision_directions_bitmask_; }

void Tile::setType(uint8_t type) { this->type_ = type; }
void Tile::setBackground(uint8_t background) { this->background_ = background; }
void Tile::setCollisionDirectionsBitmask(uint8_t collision_directions_bitmask) { this->collision_directions_bitmask_ = collision_directions_bitmask; }

bool Tile::isCollision(uint8_t player_direction) { return player_direction & this->collision_directions_bitmask_; }
