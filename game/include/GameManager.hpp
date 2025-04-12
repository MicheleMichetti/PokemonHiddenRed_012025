#include <BinaryFileManager.hpp>
#include <Map.hpp>
#include <Player.hpp>
#include <Scene.hpp>

class GameManager {
   private:
    Map* current_map_;
    Map* buffer_map_;
    Player player_;
    Scene scene_ = Scene::getInstance();

   public:
    GameManager();
    GameManager(Map current_map, Player player, BinaryFileManager binary_file_manager);
    ~GameManager();

    void setCurrentMap(Map current_map);
    void setBufferMap(Map buffer_map);
    void setPlayer(Player player);
    void setScene(/* ... */);
    void setBinaryFileManager(BinaryFileManager binary_file_manager);

    Map* getCurrentMap();
    Map* getBufferMap();
    Player getPlayer();
    Scene getScene();
    BinaryFileManager getBinaryFileManager();

    // Methods to get info from binary files
    void retrieveMapFromFile();
    void retrieveEntitiesFromFile();
    void retrieveInteractionsFromFile();
    void retrieveTilesFromFile();
    void retrieveCurrentPlayerInstance();

    // Methods to get commands from keyboard
    uint8_t retrieveCommandFromUser();
};
