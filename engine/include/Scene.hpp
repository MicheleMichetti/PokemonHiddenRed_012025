#pragma once

#include<DialogueBox.hpp>
#include<ChoiceBox.hpp>
#include<MapEngine.hpp>
#include<MenuBox.hpp>

//Forward declarations (avoid circular dependencies)
class GameManager;

class Scene {
    private:
        MapEngine map_engine_;
        ChoiceBox choice_box_;
        DialogueBox dialogue_box_;
        MenuBox menu_box_;

        Scene();
        static Scene instance;

    public:
        static void getInstance();
};