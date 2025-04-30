#include <Object.hpp>

Object::Object() : Entity() { this->dialogue[0] = "NO DATA\n"; }
Object::Object(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, _interaction::Interaction interaction, std::vector<std::string> dialogue)
    : Entity(id, type, name, movement, interaction) {
    this->dialogue = dialogue;
}
Object::~Object() {}