#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

//class ISelectCommand;
class IStateManager;

struct IMyDrawable {
    virtual void draw_into(sf::RenderWindow& window) = 0;
    virtual ~IMyDrawable() = default;
};


//////////






