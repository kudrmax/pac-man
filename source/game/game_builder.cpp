#include "game_builder.h"
#include "../config.h"
#include <thread>


void SimpleGameBuilder::create_rooms() {
    size_t count_of_rooms_x = m_width / m_room_size - 4;
    size_t count_of_rooms_y = m_height / m_room_size - 4;
    auto room_size = m_room_size;
//    auto start = 0;
    auto start = m_room_size * 2;
    std::vector<std::shared_ptr<Room>> vec;
    for (size_t i_y = 0; i_y <= count_of_rooms_y; ++i_y) {
        for (size_t i_x = 0; i_x <= count_of_rooms_x; ++i_x) {
            auto room = std::make_shared<Room>(room_size);
            room->set_position(
                    { start + static_cast<float>(i_x) * room_size, start + static_cast<float>(i_y) * room_size });
            vec.emplace_back(room);
        }
        m_rooms.push_back(vec);
        vec.clear();
    }
}

void SimpleGameBuilder::set_rooms_sides() {
    for (size_t row_n = 0; row_n < m_rooms.size(); ++row_n) {
        for (size_t col_n = 0; col_n < m_rooms[row_n].size(); ++col_n) {
            auto room = m_rooms[row_n][col_n];
            auto row_max = m_rooms.size();
            auto cal_max = m_rooms[row_n].size();
            if (col_n == 0 || col_n == m_rooms[row_n].size() - 1 ||
                row_n == 0 || row_n == m_rooms.size() - 1) {
                for (size_t i = 0; i < 4; ++i)
                    room->set_side(static_cast<Room::Direction>(i), std::make_shared<Wall>(room));
            } else if (col_n == 1 && row_n == 1) {
                room->set_side(Room::Direction::LEFT, std::make_shared<Wall>(room));
                room->set_side(Room::Direction::UP, std::make_shared<Wall>(room));
                room->set_side(Room::Direction::RIGHT, std::make_shared<Pass>(room, m_rooms[row_n][col_n + 1]));
                room->set_side(Room::Direction::DOWN, std::make_shared<Pass>(room, m_rooms[row_n + 1][col_n]));
            } else if (col_n == 1 && row_n == row_max - 2) {
                room->set_side(Room::Direction::LEFT, std::make_shared<Wall>(room));
                room->set_side(Room::Direction::UP, std::make_shared<Pass>(room, m_rooms[row_n - 1][col_n]));
                room->set_side(Room::Direction::RIGHT, std::make_shared<Pass>(room, m_rooms[row_n][col_n + 1]));
                room->set_side(Room::Direction::DOWN, std::make_shared<Wall>(room));
            } else if (col_n == cal_max - 2 && row_n == row_max - 2) {
                room->set_side(Room::Direction::LEFT, std::make_shared<Pass>(room, m_rooms[row_n][col_n - 1]));
                room->set_side(Room::Direction::UP, std::make_shared<Pass>(room, m_rooms[row_n - 1][col_n]));
                room->set_side(Room::Direction::RIGHT, std::make_shared<Wall>(room));
                room->set_side(Room::Direction::DOWN, std::make_shared<Wall>(room));
            } else if (col_n == cal_max - 2 && row_n == 1) {
                room->set_side(Room::Direction::LEFT, std::make_shared<Pass>(room, m_rooms[row_n - 1][col_n]));
                room->set_side(Room::Direction::UP, std::make_shared<Wall>(room));
                room->set_side(Room::Direction::RIGHT, std::make_shared<Wall>(room));
                room->set_side(Room::Direction::DOWN, std::make_shared<Pass>(room, m_rooms[row_n + 1][col_n]));
            } else if (col_n > 1 && col_n < cal_max - 2 && row_n == 1) {
                room->set_side(Room::Direction::LEFT, std::make_shared<Pass>(room, m_rooms[row_n][col_n - 1]));
                room->set_side(Room::Direction::UP, std::make_shared<Wall>(room));
                room->set_side(Room::Direction::RIGHT, std::make_shared<Pass>(room, m_rooms[row_n][col_n + 1]));
                room->set_side(Room::Direction::DOWN, std::make_shared<Pass>(room, m_rooms[row_n + 1][col_n]));
            } else if (col_n > 1 && col_n < cal_max - 2 && row_n == row_max - 2) {
                room->set_side(Room::Direction::LEFT, std::make_shared<Pass>(room, m_rooms[row_n][col_n - 1]));
                room->set_side(Room::Direction::UP, std::make_shared<Pass>(room, m_rooms[row_n - 1][col_n]));
                room->set_side(Room::Direction::RIGHT, std::make_shared<Pass>(room, m_rooms[row_n][col_n + 1]));
                room->set_side(Room::Direction::DOWN, std::make_shared<Wall>(room));
            } else if (row_n > 1 && row_n < row_max - 2 && col_n == 1) {
                room->set_side(Room::Direction::LEFT, std::make_shared<Wall>(room));
                room->set_side(Room::Direction::UP, std::make_shared<Pass>(room, m_rooms[row_n - 1][col_n]));
                room->set_side(Room::Direction::RIGHT, std::make_shared<Pass>(room, m_rooms[row_n][col_n + 1]));
                room->set_side(Room::Direction::DOWN, std::make_shared<Pass>(room, m_rooms[row_n + 1][col_n]));
            } else if (row_n > 1 && row_n < row_max - 2 && col_n == cal_max - 2) {
                room->set_side(Room::Direction::LEFT, std::make_shared<Pass>(room, m_rooms[row_n][col_n - 1]));
                room->set_side(Room::Direction::UP, std::make_shared<Pass>(room, m_rooms[row_n - 1][col_n]));
                room->set_side(Room::Direction::RIGHT, std::make_shared<Wall>(room));
                room->set_side(Room::Direction::DOWN, std::make_shared<Pass>(room, m_rooms[row_n + 1][col_n]));
            } else {
                room->set_side(Room::Direction::LEFT, std::make_shared<Pass>(room, m_rooms[row_n][col_n - 1]));
                room->set_side(Room::Direction::UP, std::make_shared<Pass>(room, m_rooms[row_n - 1][col_n]));
                room->set_side(Room::Direction::RIGHT, std::make_shared<Pass>(room, m_rooms[row_n][col_n + 1]));
                room->set_side(Room::Direction::DOWN, std::make_shared<Pass>(room, m_rooms[row_n + 1][col_n]));
            }
        }
    }
}

void SimpleGameBuilder::create_state(IStateManager* state_manager, std::string window_title) {
    m_game_state = std::make_unique<GameState>(state_manager, window_title);
}

void SimpleGameBuilder::set_all_to_state() {
    std::vector<std::shared_ptr<Room>> new_vec;
    for (auto&& v: m_rooms) {
        new_vec.insert(new_vec.end(), v.begin(), v.end());
    }
    m_game_state->set_maze(std::make_unique<Maze>(new_vec));
    m_game_state->set_context(std::move(m_context));
}

SimpleGameBuilder::SimpleGameBuilder(float
                                     width, float
                                     height, float
                                     room_size) :
        m_width(width), m_height(height), m_room_size(room_size) {}

void SimpleGameBuilder::create_context(float dynamic_objects_ratio) {
    // PacMan
    PacMan pacman;
    auto room = m_rooms[3][3];
    pacman.set_location(room);
    m_context.pacman = std::move(pacman);

//    auto room_for_food = m_rooms[4][4];
//    auto food = std::make_shared<Food>();
//    food->set_location(room_for_food);
//    m_context.static_objects.emplace_back(food);

    // Food
    for (size_t row_n = 1; row_n < m_rooms.size() - 1; ++row_n) {
        for (size_t col_n = 1; col_n < m_rooms[row_n].size() - 1; ++col_n) {
            auto room_food = m_rooms[row_n][col_n];
            auto food = std::make_shared<Food>();
            food->set_location(room_food);
            m_context.static_objects.push_back(food);
        }
    }

};

GameBuilderDirector::GameBuilderDirector(std::unique_ptr<IGameBuilder> ptr_builder,
                                         const std::string& window_title,
                                         float dynamic_objects_ratio) :
        m_ptr_builder(std::move(ptr_builder)), m_window_title(window_title),
        m_dynamic_objects_ratio(dynamic_objects_ratio) {}

std::unique_ptr<GameState> GameBuilderDirector::build(IStateManager* state_manager) {
    std::cout << "GameBuilderDirector::build is started" << std::endl;
    m_ptr_builder->create_rooms();
    std::cout << "SimpleGameBuilder::set_rooms_sides is started" << std::endl;
    m_ptr_builder->set_rooms_sides();
    std::cout << "SimpleGameBuilder::set_rooms_sides is done" << std::endl;
    m_ptr_builder->create_context(m_dynamic_objects_ratio);
    std::cout << "SimpleGameBuilder::create_state is started" << std::endl;
    m_ptr_builder->create_state(state_manager, m_window_title);
    std::cout << "SimpleGameBuilder::create_state is done" << std::endl;
    m_ptr_builder->set_all_to_state();
    std::cout << "GameBuilderDirector::build is done" << std::endl;
    return m_ptr_builder->get_game();
};
