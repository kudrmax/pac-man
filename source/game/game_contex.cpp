#include "game_contex.h"

void ContextManager::restore_previous_context() {
    if (m_history.size() == 1) {
        m_context = m_history.top().clone();
        return; }
    m_context = std::move(m_history.top());
    m_history.pop();
}

void ContextManager::save_current_context() {
    m_history.push(m_context.clone());
}
GameContext GameContext::clone() {
    GameContext new_context;
    new_context.pacman = pacman;
    new_context.state = state;
    for(const auto& dynamic_object : dynamic_objects)
        new_context.dynamic_objects.push_back(dynamic_object->clone());
    for(const auto& static_object : static_objects)
        new_context.static_objects.push_back(static_object->clone());
    return new_context;

}
