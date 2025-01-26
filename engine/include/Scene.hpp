#pragma once

#include<DialogueBox.hpp>
#include<ChoiceBox.hpp>
#include<MapEngine.hpp>
#include<MenuBox.hpp>

class Scene {
    private:
        MapEngine map_engine_;
        ChoiceBox choice_box_;
        DialogueBox dialogue_box_;
};