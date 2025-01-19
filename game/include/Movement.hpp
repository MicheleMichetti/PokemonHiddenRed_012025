#pragma once

#include <utils.hpp>

namespace _movement {

class Movement {
   protected:
    utils::Coordinate coordinate_;
    uint8_t direction_;

    utils::Coordinate future_coordinate_;
    uint8_t future_direction_;

   public:
    Movement();
    Movement(utils::Coordinate coordinate, uint8_t direction);
    ~Movement();

    void setCoordinate(utils::Coordinate coordinate);
    void setDirection(uint8_t direction);
    void setX(COORDINATE_TYPE x);
    void setY(COORDINATE_TYPE y);
    void setFutureCoordinate(utils::Coordinate coordinate);
    void setFutureDirection(uint8_t direction);
    void setFutureX(COORDINATE_TYPE x);
    void setFutureY(COORDINATE_TYPE y);

    const utils::Coordinate getCoordinate();
    const uint8_t getDirection();
    const COORDINATE_TYPE getX();
    const COORDINATE_TYPE getY();
    const utils::Coordinate getFutureCoordinate();
    const uint8_t getFutureDirection();
    const COORDINATE_TYPE getFutureX();
    const COORDINATE_TYPE getFutureY();

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void updateStatus();
};

};  // namespace _movement