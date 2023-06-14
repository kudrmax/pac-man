#include "entity.h"
#include "side.h"
#include "game_event.h"

void PacMan::move(Room::Direction direction) {
    m_location->get_side(direction)->enter(this);
}

void PacMan::draw_into(sf::RenderWindow& window) {
    float r = 20;
    auto circle = sf::CircleShape(r);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOrigin(r, r);
    circle.setPosition(m_location->get_position());
    window.draw(circle);
}
std::unique_ptr<IGameEvent> PacMan::visit(Food* ptr_food) {
    return std::make_unique<DeleteStaticEntity>(ptr_food);
}
std::unique_ptr<IGameEvent> PacMan::visit(Enemy* ptr_enemy) {
    return std::make_unique<LostGame>();
}
std::unique_ptr<IGameEvent> Food::accept(IVisitor* ptr_visitor) {
    return ptr_visitor->visit(this);
}
void Food::draw_into(sf::RenderWindow& window) {
    float r = 3;
    auto food = sf::CircleShape(r);
    food.setFillColor(sf::Color::Green);
    food.setOrigin(r, r);
    food.setPosition(m_location->get_position());
    window.draw(food);
}
void Enemy::draw_into(sf::RenderWindow& window) {
    float r = 10;
    auto enemy = sf::CircleShape(r);
    enemy.setFillColor(sf::Color::Red);
    enemy.setOrigin(r, r);
    enemy.setPosition(m_location->get_position());
    window.draw(enemy);
}
void Enemy::action() {
    //        srand(time(NULL));
    int dir = rand() % 4;
    float delte_time = 0.2;
//        Room::Direction direction = Room::Direction::LEFT;
    Room::Direction direction = static_cast<Room::Direction>(dir);
    if (clock.getElapsedTime() > sf::seconds(delte_time)) {
        std::cout << delte_time << std::endl;
        auto side = m_location->get_side(direction);
        side->enter(this);
        clock.restart();
    }
}
std::unique_ptr<IGameEvent> Enemy::accept(IVisitor* ptr_visitor) {
    return ptr_visitor->visit(this);
}
