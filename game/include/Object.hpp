#pragma once

#include <Entity.hpp>

class Object : public Entity {
   private:
    std::vector<std::string> dialogue;

   public:
    Object();
    Object(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, InteractionEntity interaction, std::vector<std::string> dialogue);
    ~Object();
};