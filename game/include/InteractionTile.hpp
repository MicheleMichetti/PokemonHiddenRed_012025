#include <Interaction.hpp>

class InteractionTile : public virtual _interaction::Interaction {
   public:
    InteractionTile();
    InteractionTile(uint8_t type, uint8_t status_bit_mask = 0);
    ~InteractionTile();

    void playInteraction();
    void endInteraction();

    void callFromRAM();
};