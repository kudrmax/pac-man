#include "coplex_game_builder.h"
#include "../../config.h"
#include <algorithm>

ComplexGameBuilder::ComplexGameBuilder(float width, float height, float room_size) :
        m_width(width), m_height(height), m_room_size(room_size) {}

void ComplexGameBuilder::create_rooms() {
    size_t count_of_rooms_x = m_width / m_room_size - 2;
    size_t count_of_rooms_y = m_height / m_room_size - 2;
    if (count_of_rooms_x % 2 == 0) ++count_of_rooms_x;
    if (count_of_rooms_y % 2 == 0) ++count_of_rooms_y;
    auto start_x = (m_width - count_of_rooms_x * m_room_size) / 2.0f + m_room_size / 2.0f;
    auto start_y = (m_height - count_of_rooms_y * m_room_size + m_room_size) / 2.0f;
    std::cout << "count_of_rooms_y = " << count_of_rooms_y << std::endl;
    std::cout << "start_y = " << start_y << std::endl;
    std::cout << "m_height - start_y = " << m_height - start_y << std::endl;
    std::cout << "... = " << (m_height - start_y) / count_of_rooms_y << std::endl;

    std::vector<std::unique_ptr<Room>> row_v;
    for (size_t i_y = 0; i_y < count_of_rooms_y; ++i_y) {
        for (size_t i_x = 0; i_x < count_of_rooms_x; ++i_x) {
            if (i_y % 2 == 0 && i_x % 2 == 1 || i_y % 2 == 1) {
                auto room = std::make_unique<Room>(m_room_size);
                room->set_position({ start_x + i_x * m_room_size, start_y + i_y * m_room_size });
                row_v.emplace_back(std::move(room));
            } else
                row_v.emplace_back(nullptr);
//            auto flag = rand() % 10;
//            if (flag != 0) {
//                auto room = std::make_unique<Room>(m_room_size);
//                room->set_position({ start_x + i_x * m_room_size, start_y + i_y * m_room_size });
//                row_v.emplace_back(std::move(room));
//            } else
//                row_v.emplace_back(nullptr);
        }
        m_rooms.push_back(std::move(row_v));
        row_v.clear();
    }
}

void ComplexGameBuilder::set_rooms_sides() {
    size_t row_first = 0;
    size_t row_last = m_rooms.size() - 1;
    size_t col_first = 0;
    size_t col_last = m_rooms[0].size() - 1;
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

void ComplexGameBuilder::create_context(float dynamic_objects_ratio) {

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
    for (size_t i = 0; i < config::COUNT_ENEMY; ++i) {
        if (auto index = generate_index(); index != -1) {
            auto enemy = std::make_unique<Enemy>();
            enemy->set_location(*m_rooms_for_entity[index]);
            enemy->set_previous_location();
            m_context.dynamic_objects.push_back(std::move(enemy));
            remove_from_room_for_entity(index);
        }
    }
};

void ComplexGameBuilder::create_state(IStateManager& state_manager, std::string window_title) {
    m_game_state = std::make_unique<GameState>(state_manager, window_title, sf::VideoMode(m_width, m_height));
}

void ComplexGameBuilder::set_all_to_state() {
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