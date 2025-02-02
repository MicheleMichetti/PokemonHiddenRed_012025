#pragma once

#include <bits/stdc++.h>
#include <stdint.h>
#include <allegro5/allegro.h>

#include <graphics_utils.hpp>

class Cloud {
    protected:
        graphics_utils::PixelCoordinates pixel_coordinates_;
        uint16_t px_heigth_;
        uint16_t px_width_;
    
    public:
        Cloud();
        Cloud(uint16_t px_heigth, uint16_t px_width);
        ~Cloud();

        
        
        

};