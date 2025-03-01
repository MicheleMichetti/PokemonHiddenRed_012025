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
    DRAW_TILE   = 0b00000001,
    DRAW_BKGD   = 0b00000010,
    DRAW_OBJ    = 0b00000100
    
};

enum MapStatus : uint8_t {
    UPDATE_DRAW   = 0b00000001,
    IS_BUFFER_MAP = 0b00000010
};





};