#pragma once

#include <map>
#include <utils.hpp>

namespace _interaction {

class Interaction {
   protected:
    uint8_t type_;
    uint8_t status_bit_mask_;

   public:
    Interaction();
    Interaction(uint8_t type, uint8_t status_bit_mask = 0);
    ~Interaction();

    void setType(uint8_t type);
    void setStatus(uint8_t status_bit_mask);

    uint8_t getType();
    uint8_t getStatus();

    // Interaction status reading
    bool isInteraction();
    bool isInteractionEnded();

    // Interaction status manipulation
    void enableInteraction();
    void disableInteraction();
    void playInteraction();
    void endInteraction();
    void increaseInteractionCounter();

    void callFromRAM();
};

}  // namespace _interaction