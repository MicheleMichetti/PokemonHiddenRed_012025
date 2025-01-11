#include <Interaction.hpp>

using namespace _interaction;

Interaction::Interaction() {
    type_ = 0;
    status_bit_mask_ = 0;
}
Interaction::Interaction(uint8_t type, uint8_t status_bit_mask) {
    this->type_ = type;
    this->status_bit_mask_ = status_bit_mask;
}
Interaction::~Interaction() {
    // type_ = 0;
    // status_bit_mask_ = 0;
}

void Interaction::setType(uint8_t type) { this->type_ = type; }
void Interaction::setStatus(uint8_t status_bit_mask) { this->status_bit_mask_ = status_bit_mask; }

uint8_t Interaction::getType() { return type_; }
uint8_t Interaction::getStatus() { return status_bit_mask_; }

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
void Interaction::playInteraction() {
    status_bit_mask_ |= utils::InteractionStatus::IS_PLAYING;
    increaseInteractionCounter();
}
void Interaction::endInteraction() {
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

void Interaction::callFromRAM() {}