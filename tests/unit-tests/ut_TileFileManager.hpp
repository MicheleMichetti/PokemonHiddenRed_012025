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
    printf("Tile dictionary size: %zu\n", size);
    int a = 0;
    std::cin>>a;

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
    printf("Printing tile dictionary...\n");
    al_init();
    al_install_keyboard();

    if (!al_init_image_addon()) {
        SPDLOG_ERROR("Couldn't initialize image addon");
        return false;
    }

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    // timer and an event queue to ensure the game runs at a consistent speed
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
    if (!disp) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    // al_set_window_position(disp, 300, 300);
    ALLEGRO_FONT* font = al_create_builtin_font();

    // Allegro can read in various font formats (including TTF) - but for simplicity's sake, we've used the built-in pixel font that comes with it.
    // TTF link https://liballeg.org/a5docs/trunk/font.html#ttf-fonts
    al_register_event_source(queue, al_get_keyboard_event_source());
    printf("Registered keyboard event source\n");
    al_register_event_source(queue, al_get_display_event_source(disp));
    printf("Registered display event source\n");
    al_register_event_source(queue, al_get_timer_event_source(timer));
    printf("Registered timer event source\n");

    bool done = false;
    bool redraw = false;
    ALLEGRO_EVENT event;

    al_flip_display();
    al_rest(10.0);
    al_clear_to_color(al_map_rgb(0, 0, 0));  // Clear the display
    al_flip_display();
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    al_start_timer(timer);

    char key_str = 'R';

    while (1) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_UP]) {
                    key_str = 'U';
                    redraw = true;
                }
                if (key[ALLEGRO_KEY_DOWN]) {
                    key_str = 'D';
                    redraw = true;
                }
                if (key[ALLEGRO_KEY_RIGHT]) {
                    key_str = 'R';
                    redraw = true;
                }
                if (key[ALLEGRO_KEY_LEFT]) {
                    key_str = 'L';
                    redraw = true;
                }
                if (key[ALLEGRO_KEY_S]) {
                    key_str = 'S';
                    redraw = true;
                }
                if (key[ALLEGRO_KEY_A]) {
                    key_str = 'A';
                    redraw = true;
                }
                if (key[ALLEGRO_KEY_B]) {
                    key_str = 'B';
                    redraw = true;
                }
                if (key[ALLEGRO_KEY_E]) {
                    key_str = 'E';
                    done = true;
                }
                for (int i = 0; i < ALLEGRO_KEY_MAX; i++) key[i] &= KEY_SEEN;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                printf("Key down event: %d\n", event.keyboard.keycode);
                break;

            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                printf("Key up event: %d\n", event.keyboard.keycode);
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        if (done) {
            printf("Exiting\n");
            break;
        }
        if (redraw && al_is_event_queue_empty(queue)) {
            printf("Redrawing...\n");
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));  // Clear the display
            printf("Display cleared");
            std::map<std::pair<uint8_t, uint8_t>, std::pair<Tile, TileEngine>>::iterator iterator = tile_dictionary.begin();
            graphics_utils::PixelCoordinates coord(0, 0);
            printf("Initial coord set to (%d,%d)\n", coord.x, coord.y);
            while (iterator != tile_dictionary.end()) {
                printf("Drawing at coord (%d,%d)\n", coord.x, coord.y);
                iterator->second.second.drawTile(coord);
                coord.x += 180;
                coord.y += 180;
                ++iterator;
            }
            printf("Key pressed: %c\n", key_str);
            al_flip_display();
        }
    }

    printf("Tile dictionary drawn. Exiting\n");
    al_clear_to_color(al_map_rgb(0, 0, 0));        // Clear the display
    al_destroy_display(al_get_current_display());  // Destroy the display

    return true;
}

TEST(getTiles, Positive) {
    spdlog::set_level(spdlog::level::debug);

    std::string filePath = "data/tiles/tileSample.csv.dat";
    TileFileManager tileFileManager(filePath, std::ios::in | std::ios::binary | std::ios::app);
    std::cout << tileFileManager.getStream() << std::endl;
    // int a = 0;
    // std::cin >> a;

    EXPECT_TRUE(getTiles(tileFileManager));
}

TEST(printTileDictionary, Positive) {
    spdlog::set_level(spdlog::level::debug);

    // // allegro initialization
    // al_init();
    // al_install_keyboard();
    // // timer and an event queue to ensure the game runs at a consistent speed
    // ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    // ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    // // creating display
    // ALLEGRO_DISPLAY* disp = al_create_display(180 * 4, 180 * 4);
    // // create font (probably unnecessary)
    // ALLEGRO_FONT* font = al_create_builtin_font();
    // // Allegro can read in various font formats (including TTF) - but for simplicity's sake, we've used the built-in pixel font that comes with it.
    // // TTF link https://liballeg.org/a5docs/trunk/font.html#
    // al_register_event_source(queue, al_get_keyboard_event_source());
    // al_register_event_source(queue, al_get_display_event_source(disp));
    // al_register_event_source(queue, al_get_timer_event_source(timer));

    // bool redraw = False;
    // bool done = false;
    // ALLEGRO_EVENT event;

    EXPECT_TRUE(printTileDictionary());

    // al_destroy_display(disp);
}