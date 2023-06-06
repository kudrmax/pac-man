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
std::shared_ptr<IGameEvent> PacMan::visit(Food* ptr_food) {
    return std::make_shared<DeleteStaticEntity>(ptr_food);
}
std::shared_ptr<IGameEvent> Food::accept(IVisitor* ptr_visitor) {
    return ptr_visitor->visit(this);
}
