#include "maze.h"

#include "../config.h"
#include "side.h"

Room::Direction Room::get_direction(IRoomSide& ptr_room_side) {
    if (m_sides[LEFT].get() == &ptr_room_side)
        return LEFT;
    if (m_sides[RIGHT].get() == &ptr_room_side)
        return RIGHT;
    if (m_sides[UP].get() == &ptr_room_side)
        return UP;
    if (m_sides[DOWN].get() == &ptr_room_side)
        return DOWN;
    return INVALID;
    // как это у других реализовано чекнуть
}
void Room::draw_into(sf::RenderWindow& window) {
    m_rectangle.setFillColor(config::GAME_COLOR_ROOM);
    window.draw(m_rectangle);
    m_sides[0]->draw_into(window);
    m_sides[1]->draw_into(window);
    m_sides[2]->draw_into(window);
    m_sides[3]->draw_into(window);
}
void Room::set_side(Room::Direction side, std::shared_ptr<IRoomSide>&& ptr_room_side) {
    if (side == Room::Direction::INVALID)
        throw std::runtime_error("Room::Direction == INVALID");
    else
        m_sides[side] = ptr_room_side;
}
Room::Room(float size, bool is_fillable)  : m_rectangle({ size, size }) {
    m_rectangle.setOrigin(size / 2, size / 2);
}

void Maze::draw_into(sf::RenderWindow& window) {
    for (auto& ptr_room: m_rooms) {
        ptr_room->draw_into(window);
    }
}
