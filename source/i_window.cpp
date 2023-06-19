#include "i_window.h"
#include "config.h"
#include <SFML/Graphics.hpp>

IWindowKeeper::IWindowKeeper(const sf::VideoMode& mode, const std::string& title) : m_window(mode, title) {
    m_window.setFramerateLimit(config::FRAME_RATE_LIMIT);
//    m_window.setKeyRepeatEnabled(false);
}