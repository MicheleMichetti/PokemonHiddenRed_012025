#include<ChoiceBox.hpp>

ChoiceBox::ChoiceBox() : Cloud() {
    this->is_multiple_ = false;
    for(std::string choice : this->multiple_choice_) {
        choice = nullptr;
    }
}