#include "maze.h"

#include "../config.h"
#include "side.h"

Room::Direction Room::get_direction(IRoomSide* ptr_room_side) {
    if (m_sides[LEFT].get() == ptr_room_side)
        return LEFT;
    if (m_sides[RIGHT].get() == ptr_room_side)
        return RIGHT;
    if (m_sides[UP].get() == ptr_room_side)
        return UP;
    if (m_sides[DOWN].get() == ptr_room_side)
        return DOWN;
    return INVALID;
    // как это у других реализовано
}
void Room::draw_into(sf::RenderWindow& window) {
    for (auto& ptr_side: m_sides) {
//        std::cout << "Room::draw_into is stated" << std::endl;
        ptr_side->draw_into(window);
//        std::cout << "Room::draw_into is done" << std::endl;
    }
};


void Maze::draw_into(sf::RenderWindow& window) {
    for (auto& ptr_room: m_rooms) {
//        std::cout << "Maze::draw_into is stated" << std::endl;
        ptr_room->draw_into(window);
//        std::cout << "Maze::draw_into is done" << std::endl;
    }
}
