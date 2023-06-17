#include "simple_game_builder.h"
#include "../../config.h"
#include <algorithm>

SimpleGameBuilder::SimpleGameBuilder(float width, float height, float room_size) :
        m_width(width), m_height(height), m_room_size(room_size) {}

void SimpleGameBuilder::create_rooms() {
    size_t count_of_rooms_x = static_cast<size_t>(m_width / m_room_size - 4);
    size_t count_of_rooms_y = static_cast<size_t>(m_height / m_room_size - 4);
    if (count_of_rooms_x % 2 == 1) ++count_of_rooms_x;
    if (count_of_rooms_y % 2 == 1) ++count_of_rooms_y;
    auto start_x = m_width / 2 - count_of_rooms_x * m_room_size / 2;
    auto start_y = m_height / 2 - count_of_rooms_y * m_room_size / 2;

    std::vector<std::unique_ptr<Room>> row_v;
    for (size_t i_y = 0; i_y <= count_of_rooms_y; ++i_y) {
        for (size_t i_x = 0; i_x <= count_of_rooms_x; ++i_x) {
            if (i_y % 2 == 0 && i_x % 2 == 1 || i_y % 2 == 1) {
                auto room = std::make_unique<Room>(m_room_size);
                room->set_position({ start_x + i_x * m_room_size, start_y + i_y * m_room_size });
                row_v.emplace_back(std::move(room));
            } else
                row_v.emplace_back(nullptr);
        }
        m_rooms.push_back(std::move(row_v));
        row_v.clear();
    }
}

void create_sides_for_room(std::vector<std::vector<std::unique_ptr<Room>>>& rooms,
                           const std::pair<int, int>& coords,
                           const std::vector<std::pair<Room::Direction, IRoomSide::SIDE>>& sides,
                           bool is_fillable = true) {
    using DIR = Room::Direction;
    using SIDE = IRoomSide::SIDE;
    auto row_n = coords.first;
    auto col_n = coords.second;
    auto& room = rooms[coords.first][coords.second];
    for (const auto& side: sides) {
        if (side.second == SIDE::WALL)
            room->set_side(side.first, std::make_shared<Wall>(*room));
        else if (side.second == SIDE::PASS) {
            if (side.first == DIR::LEFT)
                room->set_side(DIR::LEFT, std::make_shared<Pass>(*room, *rooms[row_n][col_n - 1]));
            if (side.first == DIR::UP)
                room->set_side(DIR::UP, std::make_shared<Pass>(*room, *rooms[row_n - 1][col_n]));
            if (side.first == DIR::RIGHT)
                room->set_side(DIR::RIGHT, std::make_shared<Pass>(*room, *rooms[row_n][col_n + 1]));
            if (side.first == DIR::DOWN)
                room->set_side(DIR::DOWN, std::make_shared<Pass>(*room, *rooms[row_n + 1][col_n]));
        }
    }
    room->set_fillable(is_fillable);
}

void SimpleGameBuilder::set_rooms_sides() {
    size_t row_first = 0;
    size_t row_last = m_rooms.size() - 1;
    size_t col_first = 0;
    size_t col_last = m_rooms[0].size() - 1;
    using DIR = Room::Direction;
    using SIDE = IRoomSide::SIDE;

    for (int row_n = 0; row_n < m_rooms.size(); ++row_n) {
        for (int col_n = 0; col_n < m_rooms[row_n].size(); ++col_n) {
            auto* this_room = m_rooms[row_n][col_n].get();
            if (this_room != nullptr) {
                auto dir = DIR::UP;
                if (row_n - 1 < 0 || m_rooms[row_n - 1][col_n] == nullptr)
                    this_room->set_side(dir, std::make_shared<Wall>(*this_room));
                else
                    this_room->set_side(dir, std::make_shared<Pass>(*this_room, *m_rooms[row_n - 1][col_n]));

                dir = DIR::LEFT;
                if (col_n - 1 < 0 || m_rooms[row_n][col_n - 1] == nullptr)
                    this_room->set_side(dir, std::make_shared<Wall>(*this_room));
                else
                    this_room->set_side(dir, std::make_shared<Pass>(*this_room, *m_rooms[row_n][col_n - 1]));

                dir = DIR::DOWN;
                if (row_n + 1 > m_rooms.size() - 1 || m_rooms[row_n + 1][col_n] == nullptr)
                    this_room->set_side(dir, std::make_shared<Wall>(*this_room));
                else
                    this_room->set_side(dir, std::make_shared<Pass>(*this_room, *m_rooms[row_n + 1][col_n]));

                dir = DIR::RIGHT;
                if (col_n + 1 > m_rooms[row_n].size() - 1 || m_rooms[row_n][col_n + 1] == nullptr)
                    this_room->set_side(dir, std::make_shared<Wall>(*this_room));
                else
                    this_room->set_side(dir, std::make_shared<Pass>(*this_room, *m_rooms[row_n][col_n + 1]));


//                this_room->set_side(DIR::UP, std::make_shared<Pass>(*m_rooms[row_n][col_n], *m_rooms[row_n][col_n]));
//                this_room->set_side(DIR::UP, std::make_shared<Wall>(*this_room));
//                this_room->set_side(DIR::DOWN, std::make_shared<Wall>(*this_room));
//                this_room->set_side(DIR::RIGHT, std::make_shared<Wall>(*this_room));
//                this_room->set_side(DIR::LEFT, std::make_shared<Wall>(*this_room));
            }
        }
    }
}


void SimpleGameBuilder::create_context(float dynamic_objects_ratio) {

    // find fillable rooms
    std::vector<Room*> fillable_rooms;
    for (const auto& row: m_rooms) {
        for (const auto& room: row) {
            if (room->is_fillable())
                fillable_rooms.push_back(room.get());
        }
    }

    // PacMan
    PacMan pacman;
    pacman.set_location(*m_rooms[3][3]);
    m_context.pacman = std::move(pacman);

    // Food
    for (auto room_food: fillable_rooms) {
        auto food = std::make_unique<Food>();
        food->set_location(*room_food);
        m_context.static_objects.push_back(std::move(food));
    }

    // Enemy
    srand(time(NULL));
    int x_rand = rand() % (m_rooms.size() - 1) + 1;
    int y_rand = rand() % (m_rooms.size() - 1) + 1;

    auto enemy1 = std::make_unique<Enemy>();
    enemy1->set_location(*m_rooms[x_rand][y_rand]);
    m_context.dynamic_objects.emplace_back(std::move(enemy1));

    auto enemy2 = std::make_unique<Enemy>();
    enemy2->set_location(*m_rooms[x_rand][y_rand]);
    m_context.dynamic_objects.emplace_back(std::move(enemy2));

    auto enemy3 = std::make_unique<Enemy>();
    enemy3->set_location(*m_rooms[x_rand][y_rand]);
    m_context.dynamic_objects.emplace_back(std::move(enemy3));
};

void SimpleGameBuilder::create_state(IStateManager& state_manager, std::string window_title) {
    m_game_state = std::make_unique<GameState>(state_manager, window_title, sf::VideoMode(m_width, m_height));
}

void SimpleGameBuilder::set_all_to_state() {
    std::vector<std::unique_ptr<Room>> new_vec;
    for (auto& row: m_rooms) {
        for (auto& room: row) {
            if (room != nullptr)
                new_vec.push_back(std::move(room));
        }
    }
    m_game_state->set_maze(std::move(Maze(new_vec)));
    m_game_state->set_context(std::move(m_context));
}