#pragma once

#include <spdlog/spdlog.h>

#include <map>
#include <utils.hpp>

namespace _interaction {

class Interaction {
   protected:
    uint32_t ID_;
    uint8_t type_;
    uint8_t status_bit_mask_;
    std::vector<std::string> dialogue_;
    std::vector<uint32_t> options_;

   public:
    Interaction();
    Interaction(uint32_t ID, uint8_t type, uint8_t status_bit_mask = 0, std::vector<std::string> dialogue = {""}, std::vector<uint32_t> options = {0});
    ~Interaction();

    void setID(uint32_t ID);
    void setType(uint8_t type);
    void setStatus(uint8_t status_bit_mask);
    void setDialogue(std::vector<std::string> dialogue);
    void setOptions(std::vector<uint32_t> options);

    uint32_t getID();
    uint8_t getType();
    uint8_t getStatus();
    std::vector<std::string> getDialogue();
    std::vector<uint32_t> getOptions();

    // Interaction status reading
    bool isInteraction();
    bool isInteractionEnded();

    // Interaction status manipulation
    void enableInteraction();
    void disableInteraction();
    void switchToPlayed();
    void switchToEnded();
    void increaseInteractionCounter();
};

}  // namespace _interaction