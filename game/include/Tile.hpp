#pragma once

#include <InteractionTile.hpp>
#include <utils.hpp>

class Tile {
   private:
    uint8_t type_;
    uint8_t background_;
    uint8_t collision_directions_bitmask_;
    uint8_t interaction_directions_bitmask_;
    InteractionTile interaction_;

   public:
    Tile();
    Tile(uint8_t type, uint8_t background, uint8_t collision_directions_bitmask, uint8_t interaction_directions_bitmask, InteractionTile interaction);
    ~Tile();

    uint8_t getType() const;
    uint8_t getBackground() const;
    uint8_t getCollisionDirectionsBitmask() const;
    uint8_t getInteractionDirectionsBitmask() const;
    InteractionTile getInteraction() const;

    void setType(uint8_t type);
    void setBackground(uint8_t background);
    void setCollisionDirectionsBitmask(uint8_t collision_directions_bitmask);
    void setInteractionDirectionsBitmask(uint8_t interaction_directions_bitmask);
    void setInteraction(InteractionTile interaction);

    bool isCollision(uint8_t player_direction);
    bool isInteraction(uint8_t player_direction);
    void playInteraction();
};