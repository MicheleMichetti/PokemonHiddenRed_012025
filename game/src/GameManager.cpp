#include <GameManager.hpp>

GameManager::GameManager() {
    this->current_map_ = nullptr;
    this->buffer_map_ = nullptr;
    this->player_ = *(new Player());
    this->binary_file_manager_ = *(new BinaryFileManager());
}
GameManager::GameManager(Map current_map, Player player, BinaryFileManager binary_file_manager) {
    this->current_map_ = current_map;
    this->buffer_map_ = nullptr;
    this->player_ = player;
    this->binary_file_manager_ = binary_file_manager;
}
GameManager::GameManager(BinaryFileManager binary_file_manager) {
    this->binary_file_manager_ = binary_file_manager;

}

GameManager::~GameManager() {
    free(this->buffer_map_);
    free(this->current_map_);
}

void GameManager::setCurrentMap(Map current_map){}
void GameManager::setBufferMap(Map buffer_map){}
void GameManager::setPlayer(Player player){}
void GameManager::setScene(/* ... */){}
void GameManager::setBinaryFileManager(BinaryFileManager binary_file_manager){}

Map* GameManager::getCurrentMap(){}
Map* GameManager::getBufferMap(){}
Player GameManager::getPlayer(){}
Scene GameManager::getScene(){}
BinaryFileManager GameManager::getBinaryFileManager(){}

//Methods to get info from binary files
void GameManager::retrieveMapFromFile(){}
void GameManager::retrieveEntitiesFromFile(){}
void GameManager::retrieveInteractionsFromFile(){}
void GameManager::retrieveTilesFromFile(){}
void GameManager::retrieveCurrentPlayerInstance(){}

//Methods to get commands from keyboard
uint8_t GameManager::retrieveCommandFromUser(){}