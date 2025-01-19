#include <Movement.hpp>

using namespace _movement;

Movement::Movement() {
    setX(0);
    setY(0);
    setDirection(0b00010000);

    setFutureX(0);
    setFutureY(0);
    setFutureDirection(0b00010000);
}

Movement::Movement(utils::Coordinate coordinate, uint8_t direction) {
    setX(coordinate.x);
    setY(coordinate.y);
    setDirection(direction);

    setFutureX(coordinate.x);
    setFutureY(coordinate.y);
    setFutureDirection(direction);
}

Movement::~Movement() {
    setX(0);
    setY(0);
    setDirection(0b00010000);

    setFutureX(0);
    setFutureY(0);
    setFutureDirection(0b00010000);
}

void Movement::setCoordinate(utils::Coordinate coordinate) {
    setX(coordinate.x);
    setY(coordinate.y);
}
void Movement::setDirection(uint8_t direction) { direction_ = direction; }
void Movement::setX(COORDINATE_TYPE X) { coordinate_.x = X; }
void Movement::setY(COORDINATE_TYPE Y) { coordinate_.y = Y; }
void Movement::setFutureCoordinate(utils::Coordinate coordinate) {
    setFutureX(coordinate.x);
    setFutureY(coordinate.y);
}
void Movement::setFutureDirection(uint8_t direction) { future_direction_ = direction; }
void Movement::setFutureX(COORDINATE_TYPE X) { future_coordinate_.x = X; }
void Movement::setFutureY(COORDINATE_TYPE Y) { future_coordinate_.y = Y; }

const utils::Coordinate Movement::getCoordinate() { return coordinate_; }
const uint8_t Movement::getDirection() { return direction_; }
const COORDINATE_TYPE Movement::getX() { return coordinate_.x; }
const COORDINATE_TYPE Movement::getY() { return coordinate_.y; }
const utils::Coordinate Movement::getFutureCoordinate() { return future_coordinate_; }
const uint8_t Movement::getFutureDirection() { return future_direction_; }
const COORDINATE_TYPE Movement::getFutureX() { return future_coordinate_.x; }
const COORDINATE_TYPE Movement::getFutureY() { return future_coordinate_.y; }

void Movement::moveUp() {
    future_coordinate_.y++;
    setFutureDirection(utils::Direction::up);
}
void Movement::moveDown() {
    future_coordinate_.y--;
    setFutureDirection(utils::Direction::down);
}
void Movement::moveRight() {
    future_coordinate_.x++;
    setFutureDirection(utils::Direction::right);
}
void Movement::moveLeft() {
    future_coordinate_.x--;
    setFutureDirection(utils::Direction::left);
}

void Movement::updateStatus() {
    setCoordinate(future_coordinate_);
    setDirection(future_direction_);
}