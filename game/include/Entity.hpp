#pragma once

#include <InteractionEntity.hpp>
#include <Movement.hpp>
#include <string>

class Entity {
   protected:
    uint32_t id;
    uint8_t type;
    std::string name;
    _movement::Movement movement;
    InteractionEntity interaction;

   public:
    Entity();
    Entity(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, InteractionEntity interaction);
    virtual ~Entity();
};
