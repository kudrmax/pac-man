#include <string>
#include "game_state.h"

struct IGameBuilder {
    virtual void create_rooms() = 0;
    virtual void set_rooms_sides() = 0;
    virtual void create_context(float dynamic_objects_ratio) = 0;
    virtual void create_state(IStateManager& state_manager, std::string window_title) = 0;
    virtual void set_all_to_state() = 0;
    virtual std::unique_ptr<GameState> get_game() = 0;
    virtual ~IGameBuilder() = default;
};

class SimpleGameBuilder : public IGameBuilder {
public:
    SimpleGameBuilder(float width, float height, float room_size);
    void create_rooms();
    void set_rooms_sides();
    void create_context(float dynamic_objects_ratio);
    void create_state(IStateManager& state_manager, std::string window_title);
    void set_all_to_state();
    std::unique_ptr<GameState> get_game();
private:
    float m_width;
    float m_height;
    float m_romm_size;
    std::vector<std::vector<std::shared_ptr<Room>>> m_rooms;
    GameContext m_context;
    std::unique_ptr<GameState> m_game_state;
};

class ComplexGameBuilder : public IGameBuilder {
public:
    ComplexGameBuilder(float width, float height, float room_size);
    void create_rooms();
    void set_rooms_sides();
    void create_context(float dynamic_objects_ratio);
    void create_state(IStateManager& state_manager, std::string window_title);
    void set_all_to_state();
    std::unique_ptr<GameState> get_game();
private:
    float m_width;
    float m_height;
    float m_romm_size;
    std::vector<std::vector<std::shared_ptr<Room>>> m_rooms;
    GameContext m_context;
    std::unique_ptr<GameState> m_game_state;
};

class GameBuilderDirector {
public:
    GameBuilderDirector(std::unique_ptr<IGameBuilder> ptr_builder, std::string window_title,
                        float dynamic_objects_ratio);
    std::unique_ptr<GameState> build(IStateManager& state_manager);
private:
    float m_dynamic_objects_ratio;
    std::string m_window_title;
};