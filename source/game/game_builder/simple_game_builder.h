#pragma once

#include "i_game_builder.h"

class SimpleGameBuilder : public IGameBuilder {
public:
    SimpleGameBuilder(float width, float height, float room_size);
    void create_rooms() override;
    void set_rooms_sides() override;
    void create_context(float dynamic_objects_ratio) override;
    void create_state(IStateManager& state_manager, std::string window_title) override;
    void set_all_to_state() override;
    std::unique_ptr<GameState> get_game() override { return std::move(m_game_state); };
private:
    void create_sides_for_room_method(const std::pair<int, int>& coords,
                                      const std::vector<std::pair<Room::Direction, IRoomSide::SIDE>>& sides) {
        using DIR = Room::Direction;
        using SIDE = IRoomSide::SIDE;
        auto row_n = coords.first;
        auto col_n = coords.second;
        auto& room = m_rooms[coords.first][coords.second];
        for (const auto& side: sides) {
            if (side.second == SIDE::WALL) {
                if (side.first == DIR::LEFT)
                    room->set_side(DIR::LEFT, std::make_shared<Wall>(*room));
                if (side.first == DIR::UP)
                    room->set_side(DIR::UP, std::make_shared<Wall>(*room));
                if (side.first == DIR::RIGHT)
                    room->set_side(DIR::RIGHT, std::make_shared<Wall>(*room));
                if (side.first == DIR::DOWN)
                    room->set_side(DIR::DOWN, std::make_shared<Wall>(*room));
            } else if (side.second == SIDE::PASS) {
                if (side.first == DIR::LEFT)
                    room->set_side(DIR::LEFT, std::make_shared<Pass>(*room, *m_rooms[row_n][col_n - 1]));
                if (side.first == DIR::UP)
                    room->set_side(DIR::UP, std::make_shared<Pass>(*room, *m_rooms[row_n - 1][col_n]));
                if (side.first == DIR::RIGHT)
                    room->set_side(DIR::RIGHT, std::make_shared<Pass>(*room, *m_rooms[row_n][col_n + 1]));
                if (side.first == DIR::DOWN)
                    room->set_side(DIR::DOWN, std::make_shared<Pass>(*room, *m_rooms[row_n + 1][col_n]));
            }
        }
    }
private:
    float m_width;
    float m_height;
    float m_room_size;
    std::vector<std::vector<std::unique_ptr<Room>>> m_rooms;
    GameContext m_context;
    std::unique_ptr<GameState> m_game_state;
};