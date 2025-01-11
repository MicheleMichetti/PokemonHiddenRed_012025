#include <Entity.hpp>

Entity::Entity() {
    this->id = 0;
    this->name = "Default_Entity";
    this->movement.setDirection(0);
    this->movement.setX(0);
    this->movement.setY(0);
    this->movement.setFutureDirection(0);
    this->movement.setFutureX(0);
    this->movement.setFutureY(0);
    this->interaction.setType(0);
    this->interaction.setStatus(0);  // as default constructor, the interaction exists but it is disabled by setting the first bit to 0.
}
Entity::Entity(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, InteractionEntity interaction) {
    this->id = id;
    this->type = type;
    this->name = name;
    this->movement = movement;
    this->interaction = interaction;
}
Entity::~Entity() {
    // TODO
}