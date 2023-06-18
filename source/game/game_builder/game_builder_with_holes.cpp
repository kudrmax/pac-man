#include "game_builder_with_holes.h"
#include "../../config.h"
#include <algorithm>

GameBuilderWithHoles::GameBuilderWithHoles(float width, float height, float room_size) :
        m_width(width), m_height(height), m_room_size(room_size) {}

void GameBuilderWithHoles::fill_rooms_for_entity() {
    for (const auto& row: m_rooms) {
        for (const auto& room: row) {
            if (room != nullptr)
                m_rooms_for_entity.push_back(room.get());
        }
    }
}
void GameBuilderWithHoles::remove_from_room_for_entity(size_t index) {
    m_rooms_for_entity.erase(m_rooms_for_entity.begin() + index);
}
auto GameBuilderWithHoles::generate_index() {
    if (!m_rooms_for_entity.empty()) {
        std::uniform_int_distribution temp{ 0, static_cast<int>(m_rooms_for_entity.size() - 1) };
        return temp(s_generator);
    }
    return -1;
}

void GameBuilderWithHoles::set_rooms_sides() {
    using DIR = Room::Direction;

    for (int row_n = 0; row_n < m_rooms.size(); ++row_n) {
        for (int col_n = 0; col_n < m_rooms[row_n].size(); ++col_n) {

            auto& this_room = m_rooms[row_n][col_n];
            if (this_room != nullptr) {
                for (int i = 0; i < 4; ++i) {
                    auto dir = static_cast<DIR>(i);
                    if (dir == Room::UP && row_n - 1 >= 0 && m_rooms[row_n - 1][col_n] != nullptr)
                        this_room->set_side(dir, std::make_shared<Pass>(*this_room, *m_rooms[row_n - 1][col_n]));
                    else if (dir == Room::LEFT && col_n - 1 >= 0 && m_rooms[row_n][col_n - 1] != nullptr)
                        this_room->set_side(dir, std::make_shared<Pass>(*this_room, *m_rooms[row_n][col_n - 1]));
                    else if (dir == Room::DOWN && row_n + 1 <= m_rooms.size() - 1 &&
                             m_rooms[row_n + 1][col_n] != nullptr)
                        this_room->set_side(dir, std::make_shared<Pass>(*this_room, *m_rooms[row_n + 1][col_n]));
                    else if (dir == Room::RIGHT && col_n + 1 <= m_rooms[row_n].size() - 1 &&
                             m_rooms[row_n][col_n + 1] != nullptr)
                        this_room->set_side(dir, std::make_shared<Pass>(*this_room, *m_rooms[row_n][col_n + 1]));
                    else
                        this_room->set_side(dir, std::make_shared<Wall>(*this_room));
                }
            }
        }
    }
}

void GameBuilderWithHoles::create_context(float dynamic_objects_ratio) {

    // find rooms_for_entity
    fill_rooms_for_entity();

    // Food
    for (size_t index = 0; index < m_rooms_for_entity.size(); ++index) {
        auto food = std::make_unique<Food>();
        food->set_location(*m_rooms_for_entity[index]);
        m_context.static_objects.push_back(std::move(food));
    }

    // PacMan
    if (auto index = generate_index(); index != -1) {
        PacMan pacman;
        pacman.set_location(*m_rooms_for_entity[index]);
        m_context.pacman = std::move(pacman);
        remove_from_room_for_entity(index);
    }

    // Enemy
    for (size_t i = 0; i < config::COUNT_ENEMY * dynamic_objects_ratio; ++i) {
        if (auto index = generate_index(); index != -1) {
            auto enemy = std::make_unique<Enemy>();
            enemy->set_location(*m_rooms_for_entity[index]);
            enemy->set_previous_location();
            m_context.dynamic_objects.push_back(std::move(enemy));
            remove_from_room_for_entity(index);
        }
    }
};

void GameBuilderWithHoles::create_state(IStateManager& state_manager, std::string window_title) {
    m_game_state = std::make_unique<GameState>(state_manager, window_title, sf::VideoMode(m_width, m_height));
}

void GameBuilderWithHoles::set_all_to_state() {
    std::vector<std::unique_ptr<Room>> rooms_without_nullptr;
    for (auto& row: m_rooms) {
        for (auto& room: row) {
            if (room != nullptr)
                rooms_without_nullptr.push_back(std::move(room));
        }
    }
    m_game_state->set_maze(Maze(rooms_without_nullptr));
    m_game_state->set_context(std::move(m_context));
}
