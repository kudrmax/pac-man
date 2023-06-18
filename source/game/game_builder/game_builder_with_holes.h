#pragma once

#include "i_game_builder.h"

struct GameBuilderWithHoles : public IGameBuilder{
    GameBuilderWithHoles(float width, float height, float room_size);
    virtual void create_rooms() = 0;
    void set_rooms_sides() override;
    void create_context(float dynamic_objects_ratio) override;
    void create_state(IStateManager& state_manager, std::string window_title) override;
    void set_all_to_state() override;
    std::unique_ptr<GameState> get_game() override { return std::move(m_game_state); };
protected:
    float m_width;
    float m_height;
    float m_room_size;
    std::vector<std::vector<std::unique_ptr<Room>>> m_rooms;
    GameContext m_context;
    std::unique_ptr<GameState> m_game_state;
protected:
    std::vector<Room*> m_rooms_for_entity;
    static inline std::mt19937 s_generator{ std::random_device{}() };
    auto generate_index();
    void remove_from_room_for_entity(size_t index);
    void fill_rooms_for_entity();
};