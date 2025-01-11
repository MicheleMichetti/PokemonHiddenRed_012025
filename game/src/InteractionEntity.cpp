#include <InteractionEntity.hpp>

void InteractionEntity::playInteraction() {
    status_bit_mask_ |= utils::InteractionStatus::IS_PLAYING;

    increaseInteractionCounter();
}
void InteractionEntity::endInteraction() {
    status_bit_mask_ |= utils::InteractionStatus::INTERACTION_ENDED;
    status_bit_mask_ & ~utils::InteractionStatus::IS_PLAYING;
}

void InteractionEntity::callFromRAM() {}