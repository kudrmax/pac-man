#include "game_state.h"
#include "side.h"
#include <string>
//#include <memory>

struct IGameBuilder {
    virtual void create_rooms() = 0;
    virtual void set_rooms_sides() = 0;
    virtual void create_context(float dynamic_objects_ratio) = 0;
    virtual void create_state(IStateManager* state_manager, std::string window_title) = 0;
    virtual void set_all_to_state() = 0;
    virtual std::unique_ptr<GameState> get_game() = 0;
    virtual ~IGameBuilder() = default;
};

class SimpleGameBuilder : public IGameBuilder {
public:

    void create_rooms() override {
        int size_room_x = 100;
        int size_room_y = 100;
        size_t count_of_room_x = 2;
        size_t count_of_room_y = 2;
        std::vector<std::shared_ptr<Room>> vec;
        for (size_t i_x = 0; i_x < count_of_room_x; ++i_x) {
            for (size_t i_y = 0; i_y < count_of_room_y; ++i_y) {
                vec.emplace_back(std::make_shared<Room>(m_room_size));
            }
            m_rooms.push_back(vec);
        }
    };

    void set_rooms_sides() override {
        for (auto& row: m_rooms) {
            for (auto& room: row) {
                for (size_t i = 0; i < 4; ++i) {
                    room->set_side(static_cast<Room::Direction>(i), std::make_shared<Wall>(*room));
                }
            }
        }
    };

    void create_context(float dynamic_objects_ratio) override {};

    void create_state(IStateManager* state_manager, std::string window_title) override {
        m_game_state = std::make_unique<GameState>(state_manager, window_title);
    };

    void set_all_to_state() override {
//        m_game_state->set_context(m_context);
        std::vector<std::shared_ptr<Room>> new_vec;
        for (auto&& v: m_rooms) {
            new_vec.insert(new_vec.end(), v.begin(), v.end());
        }
        m_game_state->set_maze(Maze{ new_vec });
    };

    std::unique_ptr<GameState> get_game() override { return std::move(m_game_state); };

    SimpleGameBuilder(float width, float height, float room_size) :
            m_width(width), m_height(height), m_room_size(room_size) {};
private:
    float m_width;
    float m_height;
    float m_room_size;
    std::vector<std::vector<std::shared_ptr<Room>>> m_rooms;
    GameContext m_context;
    std::unique_ptr<GameState> m_game_state;
};

//class ComplexGameBuilder : public IGameBuilder {
//public:
//    ComplexGameBuilder(float width, float height, float room_size);
//    void create_rooms() override;
//    void set_rooms_sides() override;
//    void create_context(float dynamic_objects_ratio) override;
//    void create_state(IStateManager& state_manager, std::string window_title) override;
//    void set_all_to_state() override;
//    std::unique_ptr<GameState> get_game() override;
//private:
//    float m_width;
//    float m_height;
//    float m_romm_size;
//    std::vector<std::vector<std::shared_ptr<Room>>> m_rooms;
//    GameContext m_context;
//    std::unique_ptr<GameState> m_game_state;
//};

class GameBuilderDirector {
public:
    GameBuilderDirector(std::unique_ptr<IGameBuilder> ptr_builder, std::string window_title,
                        float dynamic_objects_ratio) :
            m_ptr_builder(std::move(ptr_builder)), m_window_title(window_title),
            m_dynamic_objects_ratio(dynamic_objects_ratio) {};

    std::unique_ptr<GameState> build(IStateManager* state_manager) {
        state_manager->call();
        m_ptr_builder->create_rooms();
        std::cout << "GameBuilderDirector::build is started" << std::endl;
        m_ptr_builder->set_rooms_sides();
//        m_ptr_builder->create_context();
        m_ptr_builder->create_state(state_manager, m_window_title);
        m_ptr_builder->set_all_to_state();
        std::cout << "GameBuilderDirector::build is ended" << std::endl;
        return m_ptr_builder->get_game();
    };
private:
    float m_dynamic_objects_ratio;
    std::string m_window_title;
    std::unique_ptr<IGameBuilder> m_ptr_builder;
};