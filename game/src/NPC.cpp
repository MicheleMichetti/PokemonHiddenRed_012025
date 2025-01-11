#include <NPC.hpp>

NPC::NPC() : Entity() {
    this->dialogue[0] = "NO DATA\n";
    this->boundaries[0] = {0, 0};
    this->directions = (uint8_t)0;
    this->next_entity_ID[0, 0];
}
NPC::NPC(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, InteractionEntity interaction, std::vector<std::string> dialogue, std::vector<utils::Coordinate> boundaries,
         uint8_t directions, uint32_t next_entity_ID[2])
    : Entity(id, type, name, movement, interaction) {
    this->dialogue = dialogue;
    this->boundaries = boundaries;
    this->directions = directions;
    this->next_entity_ID[next_entity_ID[0], next_entity_ID[1]];
}
NPC::~NPC() {}

std::vector<std::string> NPC::getDialogue() { return this->dialogue; }
std::vector<utils::Coordinate> NPC::getBoundaries() { return this->boundaries; }
uint8_t NPC::getDirections() { return this->directions; }
uint32_t NPC::getNextEntityID(const uint8_t& index) const { return this->next_entity_ID[index]; }

void NPC::setDialogue(const std::vector<std::string> dialogue) { this->dialogue = dialogue; }
void NPC::setBoundaries(const std::vector<utils::Coordinate> boundaries) { this->boundaries = boundaries; }
void NPC::setDirections(const uint8_t& directions) { this->directions = directions; }
void NPC::setNextEntityID(uint32_t ID, uint8_t index) { this->next_entity_ID[index]; }
