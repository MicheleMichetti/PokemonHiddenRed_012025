#include<DialogueBox.hpp>

DialogueBox::DialogueBox() : Cloud() {
    this->dialogue_ = {""};
}
DialogueBox::DialogueBox(uint16_t px_heigth, uint16_t px_width, std::vector<std::string> dialogue) : Cloud(px_heigth, px_width) {
    this->dialogue_ = dialogue;
}

void DialogueBox::retrieveFilling(std::vector<std::string> dialogue) {
    this->dialogue_ = dialogue;
}