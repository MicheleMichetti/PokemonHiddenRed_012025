#pragma once

#include<Cloud.hpp>

class ChoiceBox : public Cloud {
    private:
        bool is_multiple_;
        std::string multiple_choice_[4];

    public:
        ChoiceBox();
};