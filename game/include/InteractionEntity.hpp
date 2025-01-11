#include <Interaction.hpp>

class InteractionEntity : public virtual _interaction::Interaction {
   public:
    void playInteraction();
    void endInteraction();

    void callFromRAM();
};