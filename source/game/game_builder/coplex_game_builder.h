#pragma once

#include "i_game_builder.h"

class ComplexGameBuilder : public IGameBuilder {
public:
    ComplexGameBuilder(float width, float height, float room_size);
    void create_rooms() override;
    void set_rooms_sides() override;
    void create_context(float dynamic_objects_ratio) override;
    void create_state(IStateManager& state_manager, std::string window_title) override;
    void set_all_to_state() override;
    std::unique_ptr<GameState> get_game() override { return std::move(m_game_state); };
private:
    float m_width;
    float m_height;
    float m_room_size;
    std::vector<std::vector<std::unique_ptr<Room>>> m_rooms;
    GameContext m_context;
    std::unique_ptr<GameState> m_game_state;
private:
    std::vector<Room*> m_rooms_for_entity;
    static inline std::mt19937 s_generator{ std::random_device{}() };
    auto generate_index() {
        if (!m_rooms_for_entity.empty()) {
            std::uniform_int_distribution temp{ 0, static_cast<int>(m_rooms_for_entity.size() - 1) };
            return temp(s_generator);
        }
        return -1;
    };
    void remove_from_room_for_entity(size_t index) {
        m_rooms_for_entity.erase(m_rooms_for_entity.begin() + index);
    }
    void fill_rooms_for_entity() {
        for (const auto& row: m_rooms) {
            for (const auto& room: row) {
                if (room != nullptr)
                    m_rooms_for_entity.push_back(room.get());
            }
        }
    }
};