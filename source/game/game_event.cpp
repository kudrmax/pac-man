#include "game_event.h"

void DeleteStaticEntity::handle(GameContext& context) {
    auto& vec = context.static_objects;
    auto it = std::find_if(vec.begin(), vec.end(), [this](const auto& el) { return el.get() == &m_ptr_entity; });
    if (it == vec.end())
        throw std::runtime_error{ "There is no object for delete in DeleteStaticEntity" };
    vec.erase(it);
}


