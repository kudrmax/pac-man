#include "side.h"
#include "entity.h"
#include <thread>

sf::Vector2f rotate_vector2f(const sf::Vector2f& vec, int angle) {
    sf::Transform rotation;
    rotation.rotate(angle);
    return rotation.transformPoint(vec);
}

void Wall::draw_into(sf::RenderWindow& window) {
    prepare_to_draw(m_room);
    window.draw(m_line, 2, sf::Lines);
}

void Wall::call() {
    std::cout << std::endl;
    std::cout << "m_line[0] = { " << m_line[0].position.x << ", " << m_line[0].position.y << " }\n";
    std::cout << "m_line[1] = { " << m_line[1].position.x << ", " << m_line[1].position.y << " }\n";
    std::cout << std::endl;
}

void Wall::prepare_to_draw(std::shared_ptr<Room> room) {
    //        std::cout << "prepare_to_draw\n";
    auto dir = room->get_direction(this);
    auto size = room->get_size() / 2;
    auto pos = room->get_position();
    auto vec = sf::Vector2f{ -size, 0 };
    auto rotate_vec = rotate_vector2f(vec, 90 * static_cast<int>(dir));
    auto rotate_vec2 = rotate_vector2f(rotate_vec, 90);
    auto pos0 = pos + rotate_vec + rotate_vec2;
    auto pos1 = pos + rotate_vec - rotate_vec2;
//        std::cout << "dir = " << dir << std::endl;
//        std::cout << "size = " << size << std::endl;
//        std::cout << "pos = { " << pos.x << ", " << pos.y << " }\n";
//        std::cout << "vec = { " << vec.x << ", " << vec.y << " }\n";
//        std::cout << "rotate_vec = { " << rotate_vec.x << ", " << rotate_vec.y << " }\n";
//        std::cout << "rotate_ve2 = { " << rotate_vec2.x << ", " << rotate_vec2.y << " }\n";
//        std::cout << "\npos0 = { " << pos0.x << ", " << pos0.y << " }\n";
//        std::cout << "pos1 = { " << pos1.x << ", " << pos1.y << " }\n";
    m_line[0] = pos0;
    m_line[1] = pos1;
//        std::cout << "\nm_line[0] = { " << m_line[0].position.x << ", " << m_line[0].position.y << " }\n";
//        std::cout << "m_line[1] = { " << m_line[1].position.x << ", " << m_line[1].position.y << " }\n\n";
}

void Pass::enter(IEntity* entity) {
    entity->set_location(m_room2);
}
