#pragma once

#include <cstdint>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>



namespace graphics_utils {

struct PixelCoordinates {
    uint16_t x;
    uint16_t y;
};

enum TileStatus : uint8_t {
    Draw_Tile   = 0b00000001,
    Draw_Bkgd   = 0b00000010,
    Draw_Obj    = 0b00000100,
    Coll_up    = 0b00001000,
    Coll_down  = 0b00010000,
    Coll_left  = 0b00100000,
    Coll_right = 0b01000000,
    
};

enum MapStatus : uint8_t {
    UPDATE_DRAW   = 0b00000001,
    IS_BUFFER_MAP = 0b00000010
};





};