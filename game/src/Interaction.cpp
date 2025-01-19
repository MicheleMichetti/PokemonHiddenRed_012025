#include <Interaction.hpp>

using namespace _interaction;

Interaction::Interaction() {
    type_ = 0;
    status_bit_mask_ = 0;
}
Interaction::Interaction(uint32_t ID, uint8_t type, uint8_t status_bit_mask, std::vector<std::string> dialogue, std::vector<uint32_t> options) {
    this->ID_ = ID;
    this->type_ = type;
    this->status_bit_mask_ = status_bit_mask;
    this->dialogue_ = dialogue;
    this->options_ = options;
}
Interaction::~Interaction() {}

void Interaction::setID(uint32_t ID) { this->ID_ = ID; }
void Interaction::setType(uint8_t type) { this->type_ = type; }
void Interaction::setStatus(uint8_t status_bit_mask) { this->status_bit_mask_ = status_bit_mask; }
void Interaction::setDialogue(std::vector<std::string> dialogue) { this->dialogue_ = dialogue; }
void Interaction::setOptions(std::vector<uint32_t> options) { this->options_ = options; }

uint32_t Interaction::getID() { return this->ID_; }
uint8_t Interaction::getType() { return this->type_; }
uint8_t Interaction::getStatus() { return this->status_bit_mask_; }
std::vector<std::string> Interaction::getDialogue() { return this->dialogue_; }
std::vector<uint32_t> Interaction::getOptions() { return this->options_; }

bool Interaction::isInteraction() {
    if (!(status_bit_mask_ & utils::InteractionStatus::ENABLED)) {
        return false;
    }
    if (!isInteractionEnded()) {
        return false;
    }
    return true;
}
bool Interaction::isInteractionEnded() {
    if (status_bit_mask_ & utils::InteractionStatus::INTERACTION_ENDED) {
        return true;
    }
    return false;
}

void Interaction::enableInteraction() { status_bit_mask_ |= utils::InteractionStatus::ENABLED; }
void Interaction::disableInteraction() { status_bit_mask_ & ~utils::InteractionStatus::ENABLED; }
void Interaction::switchToPlayed() {
    status_bit_mask_ |= utils::InteractionStatus::IS_PLAYING;
    increaseInteractionCounter();
}
void Interaction::switchToEnded() {
    status_bit_mask_ |= utils::InteractionStatus::INTERACTION_ENDED;
    status_bit_mask_ & ~utils::InteractionStatus::IS_PLAYING;
}
void Interaction::increaseInteractionCounter() {
    uint8_t counter = 0b00000000;
    for (uint8_t bit_pos = 4; bit_pos < 8; ++bit_pos) {
        counter |= utils::readBit<uint8_t>(status_bit_mask_, bit_pos);
    }

    if (counter >= 0b00001111) {
        return;
    }
    counter = utils::incrementByOne(counter);

    for (uint8_t bit_pos = 4; bit_pos < 8; ++bit_pos) {
        utils::setBitTo<uint8_t>(status_bit_mask_, bit_pos, utils::readBit<uint8_t>(counter, bit_pos - 4));
    }
}
