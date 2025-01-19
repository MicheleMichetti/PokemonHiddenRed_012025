#include <NPC.hpp>

NPC::NPC() : Entity() {
    this->dialogue[0] = "NO DATA\n";
    this->boundaries[0] = {0, 0};
    this->directions = (uint8_t)0;
    this->next_entity_ID[0, 0];
    this->movement_possibilities_ = 0;
}
NPC::NPC(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, InteractionEntity interaction, std::vector<std::string> dialogue, std::vector<utils::Coordinate> boundaries,
         uint8_t directions, uint32_t next_entity_ID[2])
    : Entity(id, type, name, movement, interaction) {
    this->dialogue = dialogue;
    this->boundaries = boundaries;
    this->directions = directions;
    this->next_entity_ID[next_entity_ID[0], next_entity_ID[1]];
    this->movement_possibilities_ = directions;
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

void NPC::calculateMovement() {
    uint8_t total_choices = 0;
    for (uint8_t index = 0; index < 8; ++index) {
        total_choices += utils::readBit<uint8_t>(index, movement_possibilities_);
    }
    if (total_choices == 0 || (total_choices == 1 && boundaries.size() > 0)) {
        EntityErrorMessage("Data for movement are erroneous.");
        return;
    }
    if (total_choices == 1) {
        return;
    }

    int8_t pick = (int8_t)((double)std::rand() / (double)RAND_MAX * (double)total_choices);
    uint8_t index = 0;
    for (; index < 4; ++index) {
        if (utils::readBit<uint8_t>(index, movement_possibilities_)) {
            pick--;
        }
        if (pick < 1) {
            movement_possibilities_ = 0;
            utils::setBit<uint8_t>(movement_possibilities_, index);
            movement_.setFutureDirection(movement_possibilities_);
            return;
        }
    }
    for (; index < 8; ++index) {
        if (utils::readBit<uint8_t>(index, movement_possibilities_)) {
            pick--;
        }
        if (pick < 1) {
            break;
        }
    }

    switch (index) {
        case 4:
            movement_.moveUp();
            break;
        case 5:
            movement_.moveDown();
            break;
        case 6:
            movement_.moveLeft();
            break;
        case 7:
            movement_.moveRight();
            break;
        default:
            break;
    }
}

void NPC::executeMovement() { movement_.updateStatus(); }

void NPC::playInteraction() {
    /*
    text_object
    text_human
    simple_choice (yes/no)
    multiple_choice
    collect_object
    status_change
    trigger
    trainer
    */

    switch (interaction_.getType()) {
        case (utils::InteractionType::simple_choice):

        case (utils::InteractionType::text_human):
        case (utils::InteractionType::text_object):
            for (std::string text : interaction_.getDialogue()) {
                // TODO: Implement the graphics and the fuction that will get as input "dialogue_" and print it.
                std::cout << text << std::endl;
            }
            break;

        default:
            break;
    }
}

void NPC::endInteraction() {}