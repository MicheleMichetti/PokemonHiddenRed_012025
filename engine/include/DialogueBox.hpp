#pragma once

#include<Cloud.hpp>

class Interaction;

class DialogueBox : public virtual Cloud {
    private:
        std::vector<std::string> dialogue_;

    public:
        DialogueBox();
        DialogueBox(uint16_t px_heigth, uint16_t px_width, std::vector<std::string> dialogue);
        void setDialogue(std::vector<std::string> dialogue);
};