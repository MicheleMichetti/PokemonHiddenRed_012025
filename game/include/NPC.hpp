#include <Entity.hpp>

class NPC : public Entity {
   protected:
    std::vector<std::string> dialogue;
    std::vector<utils::Coordinate> boundaries;
    uint8_t directions;
    uint32_t next_entity_ID[2];
    uint8_t movement_possibilities_;

   public:
    NPC();
    NPC(uint32_t id, uint8_t type, std::string name, _movement::Movement movement, InteractionEntity interaction, std::vector<std::string> dialogue, std::vector<utils::Coordinate> boundaries,
        uint8_t directions, uint32_t next_entity_ID[2]);
    ~NPC();

    std::vector<std::string> getDialogue();
    std::vector<utils::Coordinate> getBoundaries();
    uint8_t getDirections();
    uint32_t getNextEntityID(const uint8_t& index) const;

    void setDialogue(const std::vector<std::string> dialogue);
    void setBoundaries(const std::vector<utils::Coordinate> boundaries);
    void setDirections(const uint8_t& directions);
    void setNextEntityID(uint32_t ID, uint8_t index);

    void calculateMovement() override;
    void executeMovement() override;
};