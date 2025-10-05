#include <Tile.hpp>
#include <TileEngine.hpp>
#include <TileFileManager.hpp>

using namespace _tileFileMng;

TileFileManager::TileFileManager() : BinaryFileManager() {}

TileFileManager::TileFileManager(std::string file_name, const std::ios_base::openmode& mode) : BinaryFileManager(file_name, mode) {
    // file_name = file_name;
    std::cout << "TileFileManager constructor called with file name: " << file_name << std::endl;
}

TileFileManager::~TileFileManager() {}

// std::string TileFileManager::getFileName() { return this->getFileName(); }

// BinaryFileManager TileFileManager::getBinaryFileManager() { return this->binary_mng; }

// void TileFileManager::setFileName(std::string file_name) { this->file_name = file_name; }

// void TileFileManager::setBinaryFileManager(BinaryFileManager file_mng) { this->binary_mng = file_mng; }

void TileFileManager::retrieveTiles() {
    uint32_t position = 0;

    uint8_t dummy = 0;

    while (!stream.fail()) {
        uint8_t bkgd = 0;
        readBitsSequence(bkgd, position, BITFIELD_BKG);
        if (this->stream.fail()) {
            return;
        }
        // SPDLOG_DEBUG(("background ID: " + std::to_string(bkgd) + " at pos " + std::to_string(position)).c_str());
        printf(("background ID: %u at pos %u\n"), bkgd, position);
        position += BITFIELD_BKG;
        uint8_t object = 0;
        readBitsSequence(object, position, BITFIELD_OBJECT);
        if (this->stream.fail()) {
            return;
        }
        // SPDLOG_DEBUG(("object ID: " + std::to_string(object) + " at pos " + std::to_string(position)).c_str());
        printf(("object ID: %u at pos %u\n"), object, position);
        position += BITFIELD_OBJECT;
        uint8_t collision_bitmask = 0;
        readBitsSequence(collision_bitmask, position, COLLISION);
        if (this->stream.fail()) {
            return;
        }
        // SPDLOG_DEBUG(("collision: " + std::to_string(collision_bitmask) + " at pos " + std::to_string(position)).c_str());
        printf(("collision: %u at pos %u\n"), collision_bitmask, position);
        position += COLLISION;
        std::string bkg_image_file_name = "";
        readBitsSequence(bkg_image_file_name, position, BITFIELD_IGM_FILENAME);
        if (this->stream.fail()) {
            return;
        }
        // SPDLOG_DEBUG(("bkg img name: " + std::to_string(bkg_image_file_name) + " at pos " + std::to_string(position)).c_str());
        printf(("bkg img name: %s at pos %u\n"), bkg_image_file_name.c_str(), position);
        position += BITFIELD_IGM_FILENAME;
        std::string object_image_file_name = "";
        readBitsSequence(object_image_file_name, position, BITFIELD_IGM_FILENAME);
        if (this->stream.fail()) {
            return;
        }
        // SPDLOG_DEBUG(("object img name: " + std::to_string(object_image_file_name) + " at pos " + std::to_string(position)).c_str());
        printf(("object img name: %s at pos %u\n"), object_image_file_name.c_str(), position);
        position += BITFIELD_IGM_FILENAME;

        std::pair key = std::make_pair(bkgd, object);
        std::pair value = std::make_pair(Tile(object, bkgd, collision_bitmask), TileEngine(object_image_file_name, bkg_image_file_name));

        tile_dictionary.insert(std::make_pair(key, value));
    }

    return;
}