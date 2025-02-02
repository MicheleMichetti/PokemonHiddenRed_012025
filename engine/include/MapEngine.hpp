#pragma once

#include<TileEngine.hpp>

//using tileArray = boost::multi_array<Tile, 2>;
//using entityCoordinates = std::pair<COORDINATE_TYPE, COORDINATE_TYPE>;
//using entityMap = std::map<entityCoordinates, Entity*>;

class MapEngine {
    private:
        TileEngine tile_engine_;
};