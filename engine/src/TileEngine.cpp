#include <spdlog/spdlog.h>
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

TileEngine::TileEngine(std::string type_img_name, std::string bkgd_img_name) {
    this->ID_ = 0;
    this->status_bitmask_ = 0;
    this->coordinates_ = {0,0};
    this->type_img_name = this->tileFilesPath + type_img_name + ".png";
    this->bkgd_img_name = this->tileFilesPath + bkgd_img_name + ".png";

    printf("tileFilesPath = %s\n",tileFilesPath.c_str());

    this->background_ = al_load_bitmap(this->bkgd_img_name.c_str()); //ALLEGRO_BITMAP *al_load_bitmap(const char *filename)
    if(this->background_ == nullptr) {
        SPDLOG_ERROR(("Could not load background image " + this->bkgd_img_name).c_str());
    }
    this->status_bitmask_ |= TileStatus::Draw_Bkgd;

    this->object_ = al_load_bitmap(this->type_img_name.c_str());
    if(this->object_ == nullptr) {
        SPDLOG_ERROR(("Could not load object image " + this->type_img_name).c_str());
    }
    this->status_bitmask_ |= TileStatus::Draw_Obj;
    this->status_bitmask_ |= TileStatus::Draw_Tile;


}


TileEngine::TileEngine(uint16_t ID, graphics_utils::PixelCoordinates coordinates, ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *object)  {
    this->ID_ = ID;
    this->coordinates_ = coordinates;
    if(background != nullptr) {
        this->background_ = background;
        this->status_bitmask_ |= TileStatus::Draw_Bkgd;
    }
    if(object != nullptr) {
        this->object_ = object; 
        this->status_bitmask_ |= TileStatus::Draw_Obj;
    }
    
}
TileEngine::~TileEngine() {
    al_destroy_bitmap(this->background_);
    al_destroy_bitmap(this->object_);
    // delete background_;
    // delete object_;
}

void TileEngine::setID(const uint16_t &ID) {
    this->ID_ = ID;
}
void TileEngine::setCoordinates(const PixelCoordinates &coordinates) {
    this->coordinates_ = coordinates;
}
void TileEngine::setBackground(ALLEGRO_BITMAP *background) {
    this->background_ = background;
}
void TileEngine::setObject(ALLEGRO_BITMAP* object) {
    this->object_ = object;
}
void TileEngine::setDrawTile() {
    this->status_bitmask_ |= TileStatus::Draw_Tile;
}

uint16_t TileEngine::getID() { return this->ID_; }
PixelCoordinates TileEngine::getCoordinates() {return this->coordinates_;}
ALLEGRO_BITMAP* TileEngine::getBackground() {return this->background_;}
ALLEGRO_BITMAP* TileEngine::getObject() {return this->object_;}
bool TileEngine::getDrawTile() {
    return (this->status_bitmask_ & TileStatus::Draw_Tile);
}

void TileEngine::drawBackground() {
    if(!(this->status_bitmask_ & TileStatus::Draw_Bkgd) && this->background_ == nullptr) {
        return;
    }
    al_draw_bitmap(this->background_, coordinates_.x, coordinates_.y, 0);
}
void TileEngine::drawObject() {
    if(!(this->status_bitmask_ & TileStatus::Draw_Obj) && this->object_ == nullptr) {
        return;
    }
    al_draw_bitmap(this->object_, coordinates_.x, coordinates_.y, 0);
}
void TileEngine::drawTile() {
    // if(!(this->status_bitmask_ & TileStatus::Draw_Tile) ) {
    //     return;
    // }
    drawBackground();
    drawObject();
}
void TileEngine::drawBackground(PixelCoordinates coordinates) {
    if(!(this->status_bitmask_ & TileStatus::Draw_Bkgd) && this->background_ == nullptr) {
        return;
    }
    al_draw_bitmap(this->background_, coordinates.x, coordinates.y, 0);
}
void TileEngine::drawObject(PixelCoordinates coordinates) {
    if(!(this->status_bitmask_ & TileStatus::Draw_Obj) && this->object_ == nullptr) {
        return;
    }
    al_draw_bitmap(this->object_, coordinates.x, coordinates.y, 0);
}
void TileEngine::drawTile(PixelCoordinates coordinates) {
    // if(!(this->status_bitmask_ & TileStatus::Draw_Tile) ) {
    //     return;
    // }
    drawBackground(coordinates);
    drawObject(coordinates);
}