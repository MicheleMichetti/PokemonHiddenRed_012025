
#include <InteractionTile.hpp>

InteractionTile::InteractionTile() {
    type_ = 0;
    status_bit_mask_ = 0;
}
InteractionTile::InteractionTile(uint8_t type, uint8_t status_bit_mask) {
    this->type_ = type;
    this->status_bit_mask_ = status_bit_mask;
}
InteractionTile::~InteractionTile() {}

void InteractionTile::playInteraction() {
    status_bit_mask_ |= utils::InteractionStatus::IS_PLAYING;

    increaseInteractionCounter();
}
void InteractionTile::endInteraction() {
    status_bit_mask_ |= utils::InteractionStatus::INTERACTION_ENDED;
    status_bit_mask_ & ~utils::InteractionStatus::IS_PLAYING;
}

void InteractionTile::callFromRAM() {}