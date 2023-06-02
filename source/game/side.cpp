#include "side.h"
#include <thread>

using namespace std::chrono_literals;


void Wall::draw_into(sf::RenderWindow& window) {
//    std::cout << "Wall::draw_into\n";
//    auto pos1 = m_line[0].position;
//    auto pos2 = m_line[1].position;

//    sf::RectangleShape rec = sf::RectangleShape({ 100, 100 });
//    rec.setFillColor(sf::Color::Red);
//    window.draw(rec);
//    sf::VertexArray m_line_arr(sf::Lines, 2);
//    m_line_arr[0] = m_line[0];
//    m_line_arr[1] = m_line[1];
//    std::cout << m_line[0].position.x << "\t" << m_line[0].position.y << std::endl;
//    std::cout << m_line[1].position.x << "\t" << m_line[1].position.y << std::endl;
//    window.draw(m_line_arr);



    sf::RectangleShape rec = sf::RectangleShape({ 100, 100 });
    rec.setFillColor(sf::Color::Red);
    window.draw(rec);

//    window.draw(m_line, 2, sf::Lines);
};

Wall::Wall(Room room) : m_room(std::move(room)) {
//    auto dir = m_room.get_direction(this);
//    auto pos = m_room.get_position();
//    auto radius = m_room.get_size() / 2;
//
//    std::cout << dir << "\t" << pos.x << "\t" << pos.y << "\t" << radius << std::endl;
//
//    std::array<sf::Vector2f, 4> arr;
//    arr[0] = pos + sf::Vector2f(radius, -radius);
//    arr[1] = pos + sf::Vector2f(radius, radius);
//    arr[2] = pos + sf::Vector2f(-radius, +radius);
//    arr[3] = pos + sf::Vector2f(-radius, -radius);
//    if (dir == Room::Direction::LEFT) {
//        m_line[0] = sf::Vertex(arr[3]);
//        m_line[1] = sf::Vertex(arr[0]);
//    } else if (dir == Room::Direction::UP) {
//        m_line[0] = sf::Vertex(arr[0]);
//        m_line[1] = sf::Vertex(arr[1]);
//    } else if (dir == Room::Direction::RIGHT) {
//        m_line[0] = sf::Vertex(arr[1]);
//        m_line[1] = sf::Vertex(arr[2]);
//    } else if (dir == Room::Direction::DOWN) {
//        m_line[0] = sf::Vertex(arr[2]);
//        m_line[1] = sf::Vertex(arr[3]);
//    }
//    std::cout << m_line[0].position.x << "\t" << m_line[0].position.y << std::endl;
//    std::cout << m_line[1].position.x << "\t" << m_line[1].position.y << std::endl;
//    std::this_thread::sleep_for(3s);
}