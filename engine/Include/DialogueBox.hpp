#pragma once

#include<Cloud.hpp>

class DialogueBox : public virtual Cloud {
    private:
        std::vector<std::string> dialogue_;

    public:
        DialogueBox();
        DialogueBox(uint16_t px_heigth, uint16_t px_width, std::vector<std::string> dialogue);
        void retrieveFilling(std::vector<std::string> dialogue);
}