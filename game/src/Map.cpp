#include <spdlog/spdlog.h>
#include <thread>

#include <Map.hpp>

Map::Map() {
    this->id_ = 0;
    this->type_ = 0;
    this->map_name_ = "";
    this->length_x_ = 0;
    this->length_y_ = 0;
}

Map::Map(const uint16_t& id, const uint8_t& type, const std::string& map_name, const tileArray& tiles, const uint16_t& length_x, const uint16_t& length_y, const entityMap& entities) {
    this->id_ = id;
    this->type_ = type;
    this->map_name_ = map_name;
    this->length_x_ = length_x;
    this->length_y_ = length_y;
    this->tiles_ = tiles;
    this->entities_ = entities;
}

Map::~Map() {
    entities_.clear();
}

void Map::setId(const uint16_t& id) { this->id_ = id; }
void Map::setType(const uint8_t& type) { this->type_ = type; }
void Map::setMapName(const std::string& map_name) { this->map_name_ = map_name; }
void Map::setLengthX(const uint16_t& length_x) { this->length_x_ = length_x; }
void Map::setLengthY(const uint16_t& length_y) { this->length_y_ = length_y; }
void Map::setTiles(const tileArray& tiles) { this->tiles_ = tiles; }
void Map::setEntities(const entityMap& entities) { this->entities_ = entities; }

const uint16_t Map::getId() { return id_; }
const uint8_t Map::getType() { return type_; }
const std::string Map::getMapName() { return map_name_; }
const uint16_t Map::getLengthX() { return length_x_; }
const uint16_t Map::getLengthY() { return length_y_; }
const tileArray Map::getTiles() { return tiles_; }
const entityMap Map::getEntities() { return entities_; }

entityCoordinates Map::setCoordinates(const utils::Coordinate& coord) const { return std::make_pair(coord.x, coord.y); }

void Map::swapTiles(Tile& tile_1, Tile& tile_2) { std::swap(tile_1, tile_2); }
void Map::setTile(const utils::Coordinate& coordinate, const Tile& tile) { tiles_[coordinate.x][coordinate.y] = tile; }
void Map::resizeTiles(const uint16_t& length_x, const uint16_t& length_y) {
    if (length_x == 0 || length_y == 0) {
        SPDLOG_ERROR("The tile matrix that is being set has dimension 0. Exiting. ");
        throw std::invalid_argument("The tile matrix that is being set has dimension 0.");
        return;
    }
    tiles_.resize(boost::extents[length_x][length_y]);
    this->length_x_ = length_x;
    this->length_y_ = length_y;
}
void Map::resizeAndSetTiles(const tileArray& tiles, const uint16_t& length_x, const uint16_t& length_y) {
    resizeTiles(length_x, length_y);
    this->tiles_ = tiles;
}

bool Map::doesItCollide(const utils::Coordinate& coordinate, const uint8_t& direction) {
    Tile tile = tiles_[coordinate.x][coordinate.y];
    return tile.isCollision(direction);
}

bool Map::doesItInteract(const utils::Coordinate& coordinate, const uint8_t& direction) {
    Tile tile = tiles_[coordinate.x][coordinate.y];
    return tile.isInteraction(direction);
}

void Map::loadEntity(const utils::Coordinate& coord, Entity* entity) {
    if (entities_.count(setCoordinates(coord))) {
        // SPDLOG_ERROR(("At x="+std::string(coord.x)+" and y="+std::string(coord.y)+" there is already an entity on map "+std::string(id_)+".").c_str());
        // throw std::invalid_argument(("At x="+coordinate.x+" and y="+coordinate.y+" there is already an entity on map "+id_+".").c_str());
        return;
    }
    //entityCoordinates ent_coord = setCoordinates(coord);//std::make_pair(coord.x, coord.y);
    std::pair _argument1 = std::make_pair(setCoordinates(coord), entity);
    entities_.insert(_argument1);
}

void Map::replaceEntity(const utils::Coordinate& coordinate, Entity* entity) { entities_.at(setCoordinates(coordinate)) = entity; }

void Map::loadNextEntity(const Entity* entity) {
    /*if (entity->getNextEntityID(0) == 0) {
        return;
    }

    static NPC next_entity[2];
    next_entity[0] = NPC();

    if (entity->getNextEntityID(1) == 0) {
        return;
    }

    next_entity[1] = NPC();*/
    // TODO
}

void Map::loadEntities(const std::vector<utils::Coordinate>& coord, Entity* entities) {
    for (uint16_t entry_num = 0; entry_num < coord.size(); ++entry_num) {
        
        loadEntity(coord[entry_num], &(entities[entry_num]));
    }
    
}

void Map::updateEntityInteraction(const utils::Coordinate& coord, const InteractionEntity &inter) {
    entities_.at(setCoordinates(coord))->setInteraction(inter);

}

void Map::evaluateEntitiesMovement() {
    entityMap::iterator it = entities_.begin();
    for(; it != entities_.end(); ++it) {
        if(it->second->getType() > 2) {
            continue;
        }
        it->second->calculateMovement();
    }
}

void Map::startEntitiesMovementThread() {
    std::thread evaluateMovementThread ([this]() { this->evaluateEntitiesMovement(); });
    evaluateMovementThread.detach();
    
}
void Map::stopEntitiesMovementThread() {}