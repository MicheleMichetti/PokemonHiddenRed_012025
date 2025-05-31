//#include "ut_Tile.hpp"
#include "ut_TileFileManager.hpp"


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    std::string path = "data/";
    std::string fileName = "tileSample.csv.dat";
    

    _tileFileMng::TileFileManager tileFileManager(filePath, std::ios::in | std::ios::binary);

    return RUN_ALL_TESTS();
}