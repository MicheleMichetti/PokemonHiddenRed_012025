#pragma once

#include <BinaryFileManager.hpp>
#include <Tile.hpp>

#define BITFIELD_BKG 8
#define BITFIELD_TYPE 8
#define BITFIELD_IGM_FILENAME 56
//#define BITFIELD_INTERACT_DIR 4
//#define BITFIELD_INTERACT_ID 32

namespace _tileFileMng {

class TileFileManager : public BinaryFileManager {
    // private:
    // std::string file_name;

   public:
    TileFileManager();
    TileFileManager(std::string file_name, const std::ios_base::openmode& mode);
    ~TileFileManager();

    // std::string getFileName();
    // BinaryFileManager getBinaryFileManager();
    // void setFileName(std::string file_name);
    // void setBinaryFileManager(BinaryFileManager file_mng);

    void retrieveTiles();
};

std::map<std::pair<uint8_t, uint8_t>, Tile> tile_dictionary;

}  // namespace _tileFileMng