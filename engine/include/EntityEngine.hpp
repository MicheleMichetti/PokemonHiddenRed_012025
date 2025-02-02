#pragma once


#include<graphics_utils.hpp>

class EntityEngine {
    private:
        uint8_t status_bitmask_;
        ALLEGRO_BITMAP* background_;
        ALLEGRO_BITMAP* content_;
    
    public:
        EntityEngine();
        EntityEngine(uint8_t status_bitmask, ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* content);
        ~EntityEngine();

        void drawBackground();
        void drawContent();

};