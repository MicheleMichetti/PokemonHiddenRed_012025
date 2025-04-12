#pragma once

#include <Entity.hpp>

class Player : public Entity {
   private:
    uint8_t status_;

   public:
    Player();
    Player(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, Interaction interaction, uint8_t status);

    void setStatus(uint8_t status);

    uint8_t getStatus();

    void calculateMovement(const uint8_t& index);
    void executeMovement() override;

    void playInteraction() override;
    void endInteraction() override;
};