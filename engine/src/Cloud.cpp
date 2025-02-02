#include<Cloud.hpp>

Cloud::Cloud() {
    px_heigth_ = 0;
    px_width_ = 0;
}

Cloud::Cloud(uint16_t px_heigth, uint16_t px_width) {
    this->px_heigth_ = px_heigth;
    this->px_width_ = px_width;
}

Cloud::~Cloud() {}