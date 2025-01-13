#pragma once

#include <InteractionEntity.hpp>
#include <Movement.hpp>
#include <string>

class Entity {
   protected:
    uint32_t id_;
    uint8_t type_;
    std::string name_;
    _movement::Movement movement_;
    InteractionEntity interaction_;

   public:
    explicit Entity();
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, InteractionEntity interaction);
    virtual ~Entity() = default;

    void setID(uint32_t id);
    void setType(uint8_t type);
    void setName(std::string name);
    void setMovement(_movement::Movement movement);
    void setInteraction(InteractionEntity interaction);

    uint32_t getID();
    uint8_t getType();
    std::string getName();
    _movement::Movement getMovement();
    InteractionEntity getInteraction();

    void virtual calculateMovement() = 0;
    void virtual executeMovement() = 0;

    void EntityErrorMessage(const char* c);
};
