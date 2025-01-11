#include <Tile.hpp>
#include <utils.hpp>

Tile::Tile() {
    this->type_ = 0;
    this->background_ = 0;
    this->collision_directions_bitmask_ = 0;
    this->interaction_directions_bitmask_ = 0;
    this->interaction_ = *(new InteractionTile());
}

Tile::Tile(uint8_t type, uint8_t background, uint8_t collision_directions_bitmask, uint8_t interaction_directions_bitmask, InteractionTile interaction) {
    this->type_ = type;
    this->background_ = background;
    this->collision_directions_bitmask_ = collision_directions_bitmask;
    this->interaction_directions_bitmask_ = interaction_directions_bitmask;
    this->interaction_ = interaction;
}

Tile::~Tile() {}

uint8_t Tile::getType() const { return this->type_; }
uint8_t Tile::getBackground() const { return this->background_; }
uint8_t Tile::getCollisionDirectionsBitmask() const { return this->collision_directions_bitmask_; }
uint8_t Tile::getInteractionDirectionsBitmask() const { return this->interaction_directions_bitmask_; }
InteractionTile Tile::getInteraction() const { return this->interaction_; }

void Tile::setType(uint8_t type) { this->type_ = type; }
void Tile::setBackground(uint8_t background) { this->background_ = background; }
void Tile::setCollisionDirectionsBitmask(uint8_t collision_directions_bitmask) { this->collision_directions_bitmask_ = collision_directions_bitmask; }
void Tile::setInteractionDirectionsBitmask(uint8_t interaction_directions_bitmask) { this->interaction_directions_bitmask_ = interaction_directions_bitmask; }
void Tile::setInteraction(InteractionTile interaction) { this->interaction_ = interaction; }

bool Tile::isCollision(uint8_t player_direction) { return player_direction & this->collision_directions_bitmask_; }

bool Tile::isInteraction(uint8_t player_direction) { return player_direction & this->interaction_directions_bitmask_; }

void Tile::playInteraction() { interaction_.playInteraction(); };
