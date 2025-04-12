#pragma once

#include<mutex>

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

        static std::mutex mtx;

        Scene();
        static Scene *instancePtr;

    public:
        static Scene* getInstance();
};