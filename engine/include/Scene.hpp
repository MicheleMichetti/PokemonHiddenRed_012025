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

        void setMapEngine(MapEngine map_engine);
        void setChoiceBox(ChoiceBox choice_box);
        void setDialogueBox(DialogueBox dialogue_box);
        void setMenuBox(MenuBox menu_box);
        void setMutex();//technically unnecessary since mutex is static

        MapEngine getMapEngine();
        ChoiceBox getChoiceBox();
        DialogueBox getDialogueBox();
        MenuBox getMenuBox();
        std::mutex getMutex();//technically unnecessary since mutex is static

        void updateScene();

};