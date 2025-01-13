#pragma once

#include <NPC.hpp>
#include <Tile.hpp>
#include <boost/multi_array.hpp>
#include <iostream>
#include <map>
#include <string>

using tileArray = boost::multi_array<Tile, 2>;
using entityCoordinates = std::pair<uint16_t, uint16_t>;
using entityMap = std::map<entityCoordinates, Entity*>;

class Map {
   private:
    uint16_t id_;
    uint8_t type_;
    std::string map_name_;
    uint16_t length_x_;
    uint16_t length_y_;
    tileArray tiles_;
    entityMap entities_;

   public:
    explicit Map();
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;
    Map(const uint16_t& id, const uint8_t& type, const std::string& map_name, const tileArray& tiles, const uint16_t& length_x, const uint16_t& length_y, const entityMap& entities);
    ~Map();

    void setId(const uint16_t& id);
    void setType(const uint8_t& type);
    void setMapName(const std::string& map_name);
    void setLengthX(const uint16_t& length_x);
    void setLengthY(const uint16_t& length_y);
    void setTiles(const tileArray& tiles);
    void setEntities(const entityMap& entities);

    const uint16_t getId();
    const uint8_t getType();
    const std::string getMapName();
    const uint16_t getLengthX();
    const uint16_t getLengthY();
    const tileArray getTiles();
    const entityMap getEntities();

    entityCoordinates setCoordinates(const utils::Coordinate& coord) const;

    void swapTiles(Tile& tile_1, Tile& tile_2);
    void setTile(const utils::Coordinate& coordinate, const Tile& tile);
    void resizeTiles(const uint16_t& length_x, const uint16_t& length_y);
    void resizeAndSetTiles(const tileArray& tiles, const uint16_t& length_x, const uint16_t& length_y);

    bool doesItCollide(const utils::Coordinate& coordinate, const uint8_t& direction);
    bool doesItInteract(const utils::Coordinate& coordinate, const uint8_t& direction);

    void loadEntity(const utils::Coordinate& coord, Entity* entity);
    void replaceEntity(const utils::Coordinate& coordinate, Entity* entity);
    void loadNextEntity(const Entity* entity);
    void loadEntities(const std::vector<utils::Coordinate>& coord, Entity* entities);
    void updateEntityInteraction(const utils::Coordinate& coord, const InteractionEntity& inter);
    void evaluateEntitiesMovement();

    void startEntitiesMovementThread();
    void stopEntitiesMovementThread();
};