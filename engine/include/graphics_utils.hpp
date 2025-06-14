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

    PixelCoordinates(uint16_t x_coord = 0, uint16_t y_coord = 0) : x(x_coord), y(y_coord) {}
    bool operator==(const PixelCoordinates& other) const {
        return (x == other.x && y == other.y);
    }
    bool operator!=(const PixelCoordinates& other) const {
        return !(*this == other);
    }
    PixelCoordinates operator+(const PixelCoordinates& other) const {
        return PixelCoordinates(x + other.x, y + other.y);
    }
    PixelCoordinates operator-(const PixelCoordinates& other) const {
        return PixelCoordinates(x - other.x, y - other.y);
    }
    PixelCoordinates operator*(const PixelCoordinates& other) const {
        return PixelCoordinates(x * other.x, y * other.y);
    }
    PixelCoordinates operator/(const PixelCoordinates& other) const {
        return PixelCoordinates(x / other.x, y / other.y);
    }
    PixelCoordinates operator*(const float& scalar) const {
        return PixelCoordinates(static_cast<uint16_t>(x * scalar), static_cast<uint16_t>(y * scalar));
    }
    PixelCoordinates operator/(const float& scalar) const {
        return PixelCoordinates(static_cast<uint16_t>(x / scalar), static_cast<uint16_t>(y / scalar));
    }
    PixelCoordinates& operator+=(const PixelCoordinates& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    PixelCoordinates& operator-=(const PixelCoordinates& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    PixelCoordinates& operator*=(const PixelCoordinates& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    PixelCoordinates& operator/=(const PixelCoordinates& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }
    PixelCoordinates& operator*=(const float& scalar) {
        x = static_cast<uint16_t>(x * scalar);
        y = static_cast<uint16_t>(y * scalar);
        return *this;
    }
    PixelCoordinates& operator/=(const float& scalar) {
        x = static_cast<uint16_t>(x / scalar);
        y = static_cast<uint16_t>(y / scalar);
        return *this;
    }
    ALLEGRO_COLOR toAllegroColor() const {
        return al_map_rgb(x, y, 0); // Assuming x and y are RGB values, with z set to 0
    }
    ALLEGRO_COLOR toAllegroColor(uint8_t alpha) const {
        return al_map_rgba(x, y, 0, alpha); // Assuming x and y are RGB values, with z set to 0
    }
    ALLEGRO_COLOR toAllegroColor(uint8_t r, uint8_t g, uint8_t b) const {
        return al_map_rgb(r, g, b); // Using provided RGB values
    }
    ALLEGRO_COLOR toAllegroColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) const {
        return al_map_rgba(r, g, b, alpha); // Using provided RGBA values
    }
    // std::string toString() const {
    //     return "PixelCoordinates(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    // }
    static PixelCoordinates fromAllegroColor(ALLEGRO_COLOR color) {
        uint8_t r, g, b, a;
        al_unmap_rgba(color, &r, &g, &b, &a);
        return PixelCoordinates(r, g); // Assuming we only care about RGB values
    }
    static PixelCoordinates fromAllegroColor(ALLEGRO_COLOR color, uint8_t& alpha) {
        uint8_t r, g, b;
        al_unmap_rgba(color, &r, &g, &b, &alpha);
        return PixelCoordinates(r, g); // Assuming we only care about RGB values
    }
    static PixelCoordinates fromAllegroColor(ALLEGRO_COLOR color, uint8_t& r, uint8_t& g, uint8_t& b) {
        uint8_t a;
        al_unmap_rgba(color, &r, &g, &b, &a);
        return PixelCoordinates(r, g); // Assuming we only care about RGB values
    }
    static PixelCoordinates fromAllegroColor(ALLEGRO_COLOR color, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& alpha) {
        al_unmap_rgba(color, &r, &g, &b, &alpha);
        return PixelCoordinates(r, g); // Assuming we only care about RGB values
    }
    static PixelCoordinates fromAllegroColor(const ALLEGRO_COLOR& color) {
        uint8_t r, g, b, a;
        al_unmap_rgba(color, &r, &g, &b, &a);
        return PixelCoordinates(r, g); // Assuming we only care about RGB values
    }
    static PixelCoordinates fromAllegroColor(const ALLEGRO_COLOR& color, uint8_t& alpha) {
        uint8_t r, g, b;
        al_unmap_rgba(color, &r, &g, &b, &alpha);
        return PixelCoordinates(r, g); // Assuming we only care about RGB values
    }
    static PixelCoordinates fromAllegroColor(const ALLEGRO_COLOR& color, uint8_t& r, uint8_t& g, uint8_t& b) {
        uint8_t a;
        al_unmap_rgba(color, &r, &g, &b, &a);
        return PixelCoordinates(r, g); // Assuming we only care about RGB values
    }
    static PixelCoordinates fromAllegroColor(const ALLEGRO_COLOR& color, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& alpha) {
        al_unmap_rgba(color, &r, &g, &b, &alpha);
        return PixelCoordinates(r, g); // Assuming we only care about RGB values
    }

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