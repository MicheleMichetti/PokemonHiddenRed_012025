#include <TileFileManager.hpp>

using namespace _tileFileMng;

TileFileManager::TileFileManager() : BinaryFileManager() {};

TileFileManager::TileFileManager(std::string file_name, const std::ios_base::openmode& mode) : BinaryFileManager(file_name, mode) {
    //file_name = file_name;
};

//TileFileManager::~TileFileManager() { }

// std::string TileFileManager::getFileName() { return this->getFileName(); }

// BinaryFileManager TileFileManager::getBinaryFileManager() { return this->binary_mng; }

// void TileFileManager::setFileName(std::string file_name) { this->file_name = file_name; }

// void TileFileManager::setBinaryFileManager(BinaryFileManager file_mng) { this->binary_mng = file_mng; }

void TileFileManager::retrieveTiles() {
    uint32_t position = 0;
    while (this->getStream()->eof() == false) {
        uint8_t bkgd = uint8_t(this->readBitsAtPosition(position, BITFIELD_BKG));
        position += BITFIELD_BKG;
        uint8_t type = uint8_t(this->readBitsAtPosition(position, BITFIELD_TYPE));
        position += BITFIELD_TYPE;
        std::string image_file_name = this->readBitsAtPosition(position, BITFIELD_IGM_FILENAME);
        position += BITFIELD_IGM_FILENAME;

        std::pair key = std::make_pair(bkgd, type);

        tile_dictionary.insert(std::make_pair(key, image_file_name));
    }

    return
}