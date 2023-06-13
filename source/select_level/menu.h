#pragma once

#include "../i_draw.h"
#include "button.h"

class Menu : public IMyDrawable {
public:
    explicit Menu(IStateManager& state_manager);
    void draw_into(sf::RenderWindow& window) override;
    void process_mouse(const sf::Vector2f& pos, bool is_pressed);
private:
    std::vector<std::unique_ptr<Button>> m_buttons;
};