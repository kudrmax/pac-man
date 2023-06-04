#include "side.h"
#include <thread>

using namespace std::chrono_literals;


sf::Vector2f rotate_vector2f(const sf::Vector2f& vec, int angle){
    sf::Transform rotation;
    rotation.rotate(-angle);
    return rotation.transformPoint(vec);
}