#include<TileEngine.hpp>
#include"../../game/include/utils.hpp"

using namespace graphics_utils;

TileEngine::TileEngine() {
    this->ID_ = 0;
    this->status_bitmask_ = 0;
    this->coordinates_ = {0,0};
    this->background_ = nullptr;
    this->object_ = nullptr;
}
TileEngine::TileEngine(uint16_t ID, graphics_utils::PixelCoordinates coordinates, ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *object)  {
    this->ID_ = ID;
    this->coordinates_ = coordinates;
    if(background != nullptr) {
        this->background_ = background;
        this->status_bitmask_ |= TileStatus::DRAW_BKGD;
    }
    if(object != nullptr) {
        this->object_ = object; 
        this->status_bitmask_ |= TileStatus::DRAW_OBJ;
    }
    
}
TileEngine::~TileEngine() {
    free(this->background_);
    free(this->object_);
    // delete background_;
    // delete object_;
}

void TileEngine::setID(const uint16_t &ID) {
    this->ID_ = ID;
}
void TileEngine::setCoordinates(const graphics_utils::PixelCoordinates &coordinates) {
    this->coordinates_ = coordinates;
}
void TileEngine::setBackground(ALLEGRO_BITMAP *background) {
    this->background_ = background;
}
void TileEngine::setObject(ALLEGRO_BITMAP* object) {
    this->object_ = object;
}
void TileEngine::setDrawTile() {
    this->status_bitmask_ |= TileStatus::DRAW_TILE;
}

uint16_t TileEngine::getID() { return this->ID_; }
graphics_utils::PixelCoordinates TileEngine::getCoordinates() {return this->coordinates_;}
ALLEGRO_BITMAP* TileEngine::getBackground() {return this->background_;}
ALLEGRO_BITMAP* TileEngine::getObject() {return this->object_;}
bool TileEngine::getDrawTile() {
    return (this->status_bitmask_ & TileStatus::DRAW_TILE);
}

void TileEngine::drawBackground() {
    if(!(this->status_bitmask_ & TileStatus::DRAW_BKGD) && this->background_ == nullptr) {
        return;
    }
    al_draw_bitmap(this->background_, coordinates_.x, coordinates_.y, 0);
}
void TileEngine::drawObject() {
    if(!(this->status_bitmask_ & TileStatus::DRAW_OBJ) && this->object_ == nullptr) {
        return;
    }
    al_draw_bitmap(this->object_, coordinates_.x, coordinates_.y, 0);
}
void TileEngine::drawTile() {
    if(!(this->status_bitmask_ & TileStatus::DRAW_TILE) ) {
        return;
    }
    drawBackground();
    drawObject();
}