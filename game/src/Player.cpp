#include <Player.hpp>

Player::Player() : Entity() { this->status_ = 0; }
Player::Player(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, _interaction::Interaction interaction, uint8_t status) : Entity(id, type, name, movement, interaction) {
    this->status_ = status;
}

void Player::setStatus(uint8_t status) { this->status_ = status; }

uint8_t Player::getStatus() { return this->status_; }

void Player::calculateMovement(const uint8_t& index) {
    switch (index) {
        case utils::Direction::up:
            this->movement_.moveUp();
            break;
        case utils::Direction::down:
            this->movement_.moveDown();
            break;
        case utils::Direction::left:
            this->movement_.moveLeft();
            break;
        case utils::Direction::right:
            this->movement_.moveRight();
            break;
        default:
            SPDLOG_ERROR("The input movement is incorrect");
            break;
    }
}
void Player::executeMovement() { this->movement_.updateStatus(); }

void Player::playInteraction() {
    switch (interaction_.getType()) {
        case (utils::InteractionType::simple_choice):
        Playtext:
        case (utils::InteractionType::text_human):
        case (utils::InteractionType::text_object):
            for (std::string text : interaction_.getDialogue()) {
                // TODO: Implement the graphics and the fuction that will get as input "dialogue_" and print it.
                std::cout << text << std::endl;
            }
            break;
        case (utils::InteractionType::multiple_choice):
            //..
            goto Playtext;
        case (utils::InteractionType::status_change):
            //..
            goto Playtext;
        case (utils::InteractionType::collect_object):
            //..
            goto Playtext;
        case (utils::InteractionType::trigger):
            //..
            goto Playtext;
        case (utils::InteractionType::trainer):
            //..
            goto Playtext;
        default:
            break;
    }
}
void Player::endInteraction() { this->interaction_.endInteraction(); }