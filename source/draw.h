#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct IMyDrawable {
    virtual void draw_into(sf::RenderWindow& window) = 0;
    virtual ~IMyDrawable() = default;
};

struct Button : public IMyDrawable, public sf::RectangleShape {
    using RectangleShape::RectangleShape;
    void draw_into(sf::RenderWindow& window) override {};
private:
    bool m_is_selected = false;
    sf::Font m_font;
    sf::Text m_text;
    RectangleShape m_rectangle;
};

struct Menu : public IMyDrawable {
    void draw_into(sf::RenderWindow& window) {
        for (auto& ptr_button: m_buttons)
            ptr_button->draw_into(window);
    }
private:
    std::vector<std::unique_ptr<Button>> m_buttons;
};



