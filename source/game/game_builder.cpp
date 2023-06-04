#include "game_builder.h"
#include "../config.h"


void SimpleGameBuilder::create_rooms() {
    size_t count_of_rooms_x = m_width / m_room_size - 4;
    size_t count_of_rooms_y = m_height / m_room_size - 4;
    auto room_size = m_room_size;
    auto start = m_room_size * 2;

    std::vector<std::shared_ptr<Room>> vec;
    for (size_t i_x = 0; i_x <= count_of_rooms_x; ++i_x) {
        for (size_t i_y = 0; i_y <= count_of_rooms_y; ++i_y) {
            auto room = std::make_shared<Room>(room_size);
            room->set_position({ start + static_cast<float>(i_x) * room_size, start + static_cast<float>(i_y) * room_size });
            vec.emplace_back(room);
        }
        m_rooms.push_back(vec);
        vec.clear();
    }


//    for (size_t i_x = 0; i_x < count_of_room_x; ++i_x) {
//        for (size_t i_y = 0; i_y < count_of_room_y; ++i_y) {
//            auto room = std::make_shared<Room>(m_room_size);
//            room->set_position({ static_cast<float>(i_x) * m_room_size, static_cast<float>(i_y) * m_room_size });
//            vec.emplace_back(room);
//            std::cout << "SimpleGameBuilder::create_rooms" << std::endl;
//        }
//        m_rooms.push_back(vec);
//    }
}

void SimpleGameBuilder::set_rooms_sides() {
//    for (auto& row: m_rooms) {
//        for (auto& room: row) {
//            for (size_t i = 0; i < 4; ++i) {
//                room->set_side(static_cast<Room::Direction>(i), std::make_shared<Wall>(&*room));
//            }
//        }
//    }
//    int k = 0;
//    for (auto it_row = m_rooms.begin(); it_row != m_rooms.end(); ++it_row) {
//        if (it_row == m_rooms.begin() || it_row == --m_rooms.end()) {
//            for (auto it_room = it_row->begin(); it_room != it_row->end(); ++it_room) {
//                for (size_t i = 0; i < 4; ++i)
//                    (*it_room)->set_side(static_cast<Room::Direction>(i), std::make_shared<Wall>(&*(*it_room)));
//            }
//        } else {
//            std::cout << "NOOOOOOOO\n";
//            // просто стена самая левая
//            for (size_t i = 0; i < 4; ++i)
//                (*it_row->begin())->set_side(static_cast<Room::Direction>(i),
//                                             std::make_shared<Wall>(&*(*it_row->begin())));
//            // просто стена самая правая
//            for (size_t i = 0; i < 4; ++i)
//                (*(--(it_row->end())))->set_side(static_cast<Room::Direction>(i),
//                                                 std::make_shared<Wall>(&*(*(--(it_row->begin())))));
//            for (auto it_room = ++(it_row->begin()); it_room != --(it_row->end()); ++it_room) {
//                for (size_t i = 0; i < 4; ++i)
//                    (*it_room)->set_side(static_cast<Room::Direction>(i), std::make_shared<Wall>(&*(*it_room)));
//            }
//        }
//        std::cout << "k = " << k << "\n";
//        ++k;
//    }
//    for (auto it_row = m_rooms.begin(); it_row != m_rooms.end(); ++it_row) {
//        for (auto it_room = it_row->begin(); it_room != it_row->end(); ++it_room) {
//
//        }
//    }


    int wall_k = 0;
    int pass_k = 0;
    for (size_t row_n = 0; row_n < m_rooms.size(); ++row_n) {
        for (size_t col_n = 0; col_n < m_rooms[row_n].size(); ++col_n) {
            std::cout << "{ " << row_n << ", " << col_n << " }" << std::endl;
            auto room = m_rooms[row_n][col_n];
            if (col_n == 0 || col_n == m_rooms[row_n].size() - 1 ||
                row_n == 0 || row_n == m_rooms.size() - 1) {
                for (size_t i = 0; i < 4; ++i)
                    room->set_side(static_cast<Room::Direction>(i), std::make_shared<Wall>(&*room));
                ++wall_k;
            } else {
//                std::cout << "PASS\n";
                for (size_t i = 0; i < 4; ++i)
                    room->set_side(static_cast<Room::Direction>(i), std::make_shared<Pass>(&*room, &*room));
//                room->set_side(Room::Direction::LEFT, std::make_shared<Pass>(&*m_rooms[--row_n][col_n], &*room));
//                room->set_side(Room::Direction::RIGHT, std::make_shared<Pass>(&*room, &*m_rooms[++row_n][col_n]));
//                room->set_side(Room::Direction::UP, std::make_shared<Pass>(&*m_rooms[row_n][--col_n], &*room));
//                room->set_side(Room::Direction::DOWN, std::make_shared<Pass>(&*room, &*m_rooms[row_n][++col_n]));
                ++pass_k;
            }
        }
    }
    std::cout << "wall_k = " << wall_k << std::endl;
    std::cout << "pass_k = " << pass_k << std::endl;
    std::cout << "m_rooms.size() = " << m_rooms.size() << std::endl;
    std::cout << "m_rooms[0].size() = " << m_rooms[0].size() << std::endl;



//    for (auto& row: m_rooms) {
//        for (auto& room: row) {
//            for (size_t i = 0; i < 4; ++i) {
//                room->set_side(static_cast<Room::Direction>(i), std::make_shared<Wall>(&*room));
//            }
//        }
//    }

}

void SimpleGameBuilder::create_state(IStateManager* state_manager, std::string window_title) {
    m_game_state = std::make_unique<GameState>(state_manager, window_title);
}

void SimpleGameBuilder::set_all_to_state() {
    std::vector<std::shared_ptr<Room>> new_vec;
    for (auto&& v: m_rooms) {
        new_vec.insert(new_vec.end(), v.begin(), v.end());
    }
    std::cout << "here\n";
    m_game_state->set_maze(std::make_unique<Maze>(new_vec));
}

SimpleGameBuilder::SimpleGameBuilder(float
                                     width, float
                                     height, float
                                     room_size) :
        m_width(width), m_height(height), m_room_size(room_size) {};

GameBuilderDirector::GameBuilderDirector(std::unique_ptr<IGameBuilder>
                                         ptr_builder, std::string
                                         window_title,
                                         float
                                         dynamic_objects_ratio) :
        m_ptr_builder(std::move(ptr_builder)), m_window_title(window_title),
        m_dynamic_objects_ratio(dynamic_objects_ratio) {}

std::unique_ptr<GameState> GameBuilderDirector::build(IStateManager* state_manager) {
    std::cout << "GameBuilderDirector::build is started" << std::endl;
    m_ptr_builder->create_rooms();
    std::cout << "SimpleGameBuilder::set_rooms_sides is started" << std::endl;
    m_ptr_builder->set_rooms_sides();
    std::cout << "SimpleGameBuilder::set_rooms_sides is done" << std::endl;
//        m_ptr_builder->create_context();
    std::cout << "SimpleGameBuilder::create_state is started" << std::endl;
    m_ptr_builder->create_state(state_manager, m_window_title);
    std::cout << "SimpleGameBuilder::create_state is done" << std::endl;
    m_ptr_builder->set_all_to_state();
    std::cout << "GameBuilderDirector::build is done" << std::endl;
    return m_ptr_builder->get_game();
};
