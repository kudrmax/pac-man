#include "side.h"
#include "entity.h"
#include <thread>

sf::Vector2f Wall::rotate_vector2f(const sf::Vector2f& vec, int angle) {
    sf::Transform rotation;
    rotation.rotate(angle);
    return rotation.transformPoint(vec);
}

void Wall::draw_into(sf::RenderWindow& window) {
    prepare_to_draw(m_room);
    window.draw(m_line, 2, sf::Lines);
}

void Wall::prepare_to_draw(Room& room) {
    auto dir = room.get_direction(*this);
    auto size = room.get_size() / 2;
    auto pos = room.get_position();
    auto vec = sf::Vector2f{ -size, 0 };
    auto rotate_vec = rotate_vector2f(vec, 90 * static_cast<int>(dir));
    auto rotate_vec2 = rotate_vector2f(rotate_vec, 90);
    auto pos0 = pos + rotate_vec + rotate_vec2;
    auto pos1 = pos + rotate_vec - rotate_vec2;
    m_line[0] = pos0;
    m_line[1] = pos1;
}

void Pass::enter(IEntity& entity) {
    entity.set_location(entity.get_location() == &m_room2 ? m_room1 : m_room2);
}
