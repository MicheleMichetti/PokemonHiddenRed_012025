#include<Scene.hpp>

Scene::Scene() {
    this->choice_box_ = *(new ChoiceBox());
    this->menu_box_ = *(new MenuBox());
    this->dialogue_box_ = *(new DialogueBox());
    this->map_engine_ = *(new MapEngine());
}

Scene::getInstance() {
    if(instancePtr != nullptr) {
        return;
    }
    std::lock_guard<std::mutex> lock(mtx);
    instancePtr = new Scene();
    return instancePtr;
}