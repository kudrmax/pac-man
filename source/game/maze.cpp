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
//    for (auto& ptr_side: m_sides) {
//        std::cout << "Room::draw_into is stated" << std::endl;
//        ptr_side->draw_into(window);
//        std::cout << "Room::draw_into is done" << std::endl;
//    }
    std::cout << "Room::draw_into start\n";
    std::cout << m_sides.empty();
    m_sides[0]->call();
    m_sides[0]->draw_into(window);
    std::cout << "Room::draw_into 0\n";
    m_sides[1]->draw_into(window);
    std::cout << "Room::draw_into 1\n";
    m_sides[2]->draw_into(window);
    std::cout << "Room::draw_into 2\n";
    m_sides[3]->draw_into(window);
    std::cout << "Room::draw_into 3 (end)\n";
};


void Maze::draw_into(sf::RenderWindow& window) {
    std::cout << "Maze::draw_into is stated" << std::endl;
    for (auto& ptr_room: m_rooms) {
        ptr_room->draw_into(window);
    }
    std::cout << "Maze::draw_into is done" << std::endl;
}
