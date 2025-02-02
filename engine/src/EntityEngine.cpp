#include<EntityEngine.hpp>

EntityEngine::EntityEngine() {
    this->status_bitmask_ = 0;
    this->background_ = nullptr;
    this->content_ = nullptr;
}
EntityEngine::EntityEngine(uint8_t status_bitmask, ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* content) {
    this->status_bitmask_ = status_bitmask;
    this->background_ = background;
    this->content_ = content;
}
EntityEngine::~EntityEngine() {}

void EntityEngine::drawBackground() {}
void EntityEngine::drawContent() {}