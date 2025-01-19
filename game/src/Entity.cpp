#include <Entity.hpp>

Entity::Entity() {
    this->id_ = 0;
    this->name_ = "Default_Entity";
    this->movement_.setDirection(0);
    this->movement_.setX(0);
    this->movement_.setY(0);
    this->movement_.setFutureDirection(0);
    this->movement_.setFutureX(0);
    this->movement_.setFutureY(0);
    for(InteractionEntity interact : interaction_) {
        interact.setType(0);
        interact.setStatus(0);  // as default constructor, the interaction exists but it is disabled by setting the first bit to 0.
    }
}
Entity::Entity(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, std::vector<InteractionEntity> interaction) {
    this->id_ = id;
    this->type_ = type;
    this->name_ = name;
    this->movement_ = movement;
    this->interaction_ = interaction;
}

void Entity::setID(uint32_t id) { this->id_ = id; }
void Entity::setType(uint8_t type) { this->type_ = type; }
void Entity::setName(std::string name) { this->name_ = name; }
void Entity::setMovement(_movement::Movement movement) { this->movement_ = movement; }
void Entity::setInteraction(std::vector<InteractionEntity> interaction) { this->interaction_ = interaction; }

uint32_t Entity::getID() { return id_; }
uint8_t Entity::getType() { return type_; }
std::string Entity::getName() { return name_; }
_movement::Movement Entity::getMovement() { return movement_; }
std::vector<InteractionEntity> Entity::getInteraction() { return interaction_; }

void Entity::EntityErrorMessage(const char* c) {
    SPDLOG_ERROR(c);
    throw std::runtime_error(c);
}