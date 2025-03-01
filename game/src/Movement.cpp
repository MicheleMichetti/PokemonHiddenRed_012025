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
    setFutureDirection(utils::Direction::up);
    if(this->direction_ != this->future_direction_) {
        return;
    }
    future_coordinate_.y++;
    
}
void Movement::moveDown() {
    setFutureDirection(utils::Direction::down);
    if(this->direction_ != this->future_direction_) {
        return;
    }
    future_coordinate_.y--;
    
}
void Movement::moveRight() {
    setFutureDirection(utils::Direction::right);
    if(this->direction_ != this->future_direction_) {
        return;
    }
    future_coordinate_.x++;

}
void Movement::moveLeft() {
    setFutureDirection(utils::Direction::left);
    if(this->direction_ != this->future_direction_) {
        return;
    }
    future_coordinate_.x--;
    
}

void Movement::updateStatus() {
    setCoordinate(future_coordinate_);
    setDirection(future_direction_);
}