#include <TileFileManager.hpp>

#include "gtest/gtest.h"

using namespace _tileFileMng

bool loadTiles(const std::string &filePath) {
    TileFileManager tileFileManager(filePath, std::ios::in | std::ios::binary);
    if (!tileFileManager.isOpen()) {
        std::cerr << "Failed to open tile file: " << filePath << std::endl;
        return false;
    }
    tileFileManager.retrieveTiles();
    std::cout << "Tile file loaded successfully: " << filePath << std::endl;
    // Assuming retrieveTiles populates the tile dictionary
    // If you need to check the contents of the tile dictionary, you can do so here.
    // For example, you can print the size of the tile dictionary:
    std::cout << "Tile dictionary size: " << tileFileManager.tile_dictionary.size() << std::endl;
    // If you want to check if a specific tile exists, you can do so here.
    // Example: Check if a tile with coordinates (0, 0) exists
    auto it = tileFileManager.tile_dictionary.find({0, 0});
    if (it != tileFileManager.tile_dictionary.end()) {
        std::cout << "Tile found at (0, 0)" << std::endl;
        return true;
    } else {
        std::cout << "Tile not found at (0, 0)" << std::endl;
    }
    // Return true if the file was loaded successfully
    // You can also return false if you want to indicate failure in loading the file.
    // For now, we assume the file is loaded successfully if we reach this point.
    // Note: You may want to handle exceptions or errors in a more robust way in a real application.    
    return false;
}