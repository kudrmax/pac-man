#include "game_event.h"

void DeleteStaticEntity::handle(GameContext* context) {
    auto& vec = context->static_objects;
    auto it = std::find_if(vec.begin(), vec.end(), [&](auto el) { return el.get() == m_ptr_entity; });
    vec.erase(it);
}

void LostGame::handle(GameContext* context) {
    context->state = GameContext::LOST;

}


