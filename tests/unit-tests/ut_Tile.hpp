#include <Tile.hpp>

#include "gtest/gtest.h"

bool collision(uint8_t direction) {
    InteractionTile interTile;
    Tile testTile(0, 0, 0b00001010, 0b00000101, interTile);

    std::cout << "Test Collision " << direction << std::endl;

    return testTile.isCollision(direction);
}

bool interaction(uint8_t direction) {
    InteractionTile interTile;
    Tile testTile(0, 0, 0b00001010, 0b00000101, interTile);

    std::cout << "Test Interaction " << direction << std::endl;

    return testTile.isInteraction(direction);
}

TEST(collision, Positive) {
    EXPECT_FALSE(collision(utils::Direction::up));
    EXPECT_TRUE(collision(utils::Direction::down));
    EXPECT_FALSE(collision(utils::Direction::left));
    EXPECT_TRUE(collision(utils::Direction::right));
    EXPECT_FALSE(collision(utils::Direction::none));
}

TEST(interaction, Positive) {
    EXPECT_TRUE(interaction(utils::Direction::up));
    EXPECT_FALSE(interaction(utils::Direction::down));
    EXPECT_TRUE(interaction(utils::Direction::left));
    EXPECT_FALSE(interaction(utils::Direction::right));
    EXPECT_FALSE(interaction(utils::Direction::none));
}