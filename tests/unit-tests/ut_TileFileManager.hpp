#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <spdlog/spdlog.h>

#include <Tile.hpp>
#include <TileEngine.hpp>
#include <TileFileManager.hpp>
#include <graphics_utils.hpp>

#include "gtest/gtest.h"

#define KEY_SEEN 1
#define KEY_RELEASED 2

using namespace _tileFileMng;

bool getTiles(TileFileManager& tile_file_manager) {
    tile_file_manager.retrieveTiles();

    size_t size = tile_dictionary.size();

    for (size_t i = 0; i < size; ++i) {
        std::pair<uint8_t, uint8_t> key(i, 0);
        if (tile_dictionary.find(key) == tile_dictionary.end()) {
            std::cout << "tile_dictionary does not contain the expected tile with key (" << (uint8_t)i << ", " << 0 /*(uint8_t)i*/ << ")" << std::endl;
            return false;
        }
    }

    std::map<std::pair<uint8_t, uint8_t>, std::pair<Tile, TileEngine>>::iterator iterator = tile_dictionary.begin();
    while (iterator != tile_dictionary.end()) {
        size--;
        if (size == 0) {
            break;
        }
    }

    if (size != 0 || iterator != tile_dictionary.end()) {
        std::cout << "Size is not coherent with number of entries in the dictionary" << std::endl;
        // free(iterator);
        return false;
    }

    return true;
}

bool printTileDictionary() {
    al_init();
    al_install_keyboard();

    if (!al_init_image_addon()) {
        SPDLOG_ERROR("Couldn't initialize image addon");
        return false;
    }

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    // timer and an event queue to ensure the game runs at a consistent speed
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(180 * 4, 180 * 4);
    ALLEGRO_FONT* font = al_create_builtin_font();

    // Allegro can read in various font formats (including TTF) - but for simplicity's sake, we've used the built-in pixel font that comes with it.
    // TTF link https://liballeg.org/a5docs/trunk/font.html#ttf-fonts
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    al_start_timer(timer);

    // while (1) {
    //     al_wait_for_event(queue, &event);
    //     switch (event.type) {
    //         case ALLEGRO_EVENT_TIMER:
    //             if (key[ALLEGRO_KEY_ESCAPE]) {
    //                 done = true;
    //             }
    //             for (int i = 0; i < ALLEGRO_KEY_MAX; i++) key[i] &= KEY_SEEN;
    //             break;
    //         case ALLEGRO_EVENT_KEY_DOWN:
    //             key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
    //             break;

    //         case ALLEGRO_EVENT_KEY_UP:
    //             key[event.keyboard.keycode] &= KEY_RELEASED;
    //             break;

    //         case ALLEGRO_EVENT_DISPLAY_CLOSE:
    //             done = true;
    //             break;
    //     }
    //     if (done) {
    //         break;
    //     }
    //     std::map<std::pair<uint8_t, uint8_t>, std::pair<Tile, TileEngine>>::iterator iterator = tile_dictionary.begin();
    //     graphics_utils::PixelCoordinates coord(0, 0);
    //     while (iterator != tile_dictionary.end()) {
    //         iterator->second.second.drawTile(coord);
    //         coord.x += 180;
    //         coord.y += 180;
    //         ++iterator;
    //     }
    // }

    std::map<std::pair<uint8_t, uint8_t>, std::pair<Tile, TileEngine>>::iterator iterator = tile_dictionary.begin();
    graphics_utils::PixelCoordinates coord(0, 0);
    while (iterator != tile_dictionary.end()) {
            iterator->second.second.drawTile(coord);
            coord.x += 180;
            coord.y += 180;
            ++iterator;
        }

    al_flip_display();
    int a = 0;
    std::cin >> a;  // Wait for user input to exit
    // al_rest(2.0); // Pause for 2 seconds to view the drawn tiles
    for (unsigned int i = 0; i < 1000000000000000; ++i) {
        int t = i;  // Dummy operation to keep the program running for a while
        if (i % 100000000 == 0) {
            al_flip_display();  // Update the display every 100 million iterations
        }
    }
    al_clear_to_color(al_map_rgb(0, 0, 0));        // Clear the display
    al_destroy_display(al_get_current_display());  // Destroy the display

    return true;
}

TEST(getTiles, Positive) {
    std::string filePath = "data/tiles/tileSample";
    TileFileManager tileFileManager(filePath, std::ios::in | std::ios::binary);

    EXPECT_TRUE(getTiles(tileFileManager));
}

TEST(printTileDictionary, Positive) {
    ALLEGRO_DISPLAY* disp = al_create_display(180 * 4, 180 * 4);

    EXPECT_TRUE(printTileDictionary());

    al_destroy_display(disp);
}