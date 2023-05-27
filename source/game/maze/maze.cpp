#include "maze.h"

#include "../../config.h"

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
};

Wall::Wall(Room room) : m_room(std::move(room)) {
    auto dir = m_room.get_direction(this);
    auto pos = m_room.get_position();
    auto radius = m_room.get_size() / 2;

    std::array<sf::Vector2f, 4> arr;
    arr[0] = pos + sf::Vector2f(radius, -radius);
    arr[1] = pos + sf::Vector2f(radius, radius);
    arr[2] = pos + sf::Vector2f(-radius, +radius);
    arr[3] = pos + sf::Vector2f(-radius, -radius);
    if (dir == Room::Direction::LEFT) {
        m_line[0] = sf::Vertex(arr[3]);
        m_line[1] = sf::Vertex(arr[0]);
    } else if (dir == Room::Direction::UP) {
        m_line[0] = sf::Vertex(arr[0]);
        m_line[1] = sf::Vertex(arr[1]);
    } else if (dir == Room::Direction::RIGHT) {
        m_line[0] = sf::Vertex(arr[1]);
        m_line[1] = sf::Vertex(arr[2]);
    } else if (dir == Room::Direction::DOWN) {
        m_line[0] = sf::Vertex(arr[2]);
        m_line[1] = sf::Vertex(arr[3]);
    }
};