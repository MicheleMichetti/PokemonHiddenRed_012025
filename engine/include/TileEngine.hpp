#pragma once

#include <cstdint>
#include <string>
#include<graphics_utils.hpp>

using namespace graphics_utils;

class TileEngine {

    private:
        uint16_t ID_;
        std::string type_img_name;
        std::string bkgd_img_name;
        PixelCoordinates coordinates_;
        uint8_t status_bitmask_;
        ALLEGRO_BITMAP* background_;
        ALLEGRO_BITMAP* object_;

    public:
        TileEngine();
        TileEngine(std::string type_img_name, std::string bkgd_img_name);
        TileEngine(uint16_t ID, graphics_utils::PixelCoordinates coordinates, ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *object);
        ~TileEngine();

        void setID(const uint16_t &ID);
        void setCoordinates(const graphics_utils::PixelCoordinates &coordinates);
        void setBackground(ALLEGRO_BITMAP *background);
        void setObject(ALLEGRO_BITMAP* object);
        void setDrawTile();

        uint16_t getID();
        graphics_utils::PixelCoordinates getCoordinates();
        ALLEGRO_BITMAP* getBackground();
        ALLEGRO_BITMAP* getObject();
        bool getDrawTile();

        void drawBackground();
        void drawObject();
        void drawTile();
        void drawBackground(PixelCoordinates coordinates);
        void drawObject(PixelCoordinates coordinates);
        void drawTile(PixelCoordinates coordinates);

};