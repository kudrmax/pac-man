#include "i_window.h"
#include <SFML/Graphics.hpp>

IWindowKeeper::IWindowKeeper(const sf::VideoMode& mode, const std::string& title) : m_window(mode, title) {}