#include "game_builder.h"


void SimpleGameBuilder::create_rooms() {
//    int size_room_x = 50;
//    int size_room_y = 100;
    size_t count_of_room_x = 1;
    size_t count_of_room_y = 1;
    std::vector<std::shared_ptr<Room>> vec;
    for (size_t i_x = 0; i_x < count_of_room_x; ++i_x) {
        for (size_t i_y = 0; i_y < count_of_room_y; ++i_y) {
//            std::cout << "get_size = " << room->get_size();
//            std::cout << "m_room_size = " << m_room_size;
            vec.emplace_back(std::make_shared<Room>(m_room_size));
            std::cout << "SimpleGameBuilder::create_rooms" << std::endl;

        }
        m_rooms.push_back(vec);
    }
}

void SimpleGameBuilder::set_rooms_sides() {
    for (auto& row: m_rooms) {
        for (auto& room: row) {
            for (size_t i = 0; i < 4; ++i) {
//                auto side = std::make_shared<Wall>(*room);
//                auto dir = static_cast<Room::Direction>(i);
                room->set_side(static_cast<Room::Direction>(i), std::make_shared<Wall>(*room));
//                room->set_side(dir, std::make_shared<Wall>(*room));
//                std::cout << "Calling\n:";
//                room->get_side(dir)->call();
//                std::cout << "Stop\n:";
//                room->set_position({static_cast<float>(i*50), static_cast<float>(i*50)});
                auto side = room->get_side(static_cast<Room::Direction>(i));
                side->call();
            }
            std::cout << "get_size_sides = " << room->get_size_sides() << std::endl;
        }
    }
}

void SimpleGameBuilder::create_state(IStateManager* state_manager, std::string window_title) {
    m_game_state = std::make_unique<GameState>(state_manager, window_title);
}

void SimpleGameBuilder::set_all_to_state() {
//        m_game_state->set_context(m_context);
    std::vector<std::shared_ptr<Room>> new_vec;
    for (auto&& v: m_rooms) {
        new_vec.insert(new_vec.end(), v.begin(), v.end());
//        std::cout << "get_size = " << (*new_vec.begin())->get_size() << std::endl;
    }
    m_game_state->set_maze(Maze{ new_vec });
}

SimpleGameBuilder::SimpleGameBuilder(float width, float height, float room_size) :
        m_width(width), m_height(height), m_room_size(room_size) {};

GameBuilderDirector::GameBuilderDirector(std::unique_ptr<IGameBuilder> ptr_builder, std::string window_title,
                                         float dynamic_objects_ratio) :
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
