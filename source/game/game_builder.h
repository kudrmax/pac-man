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
    SimpleGameBuilder(float width, float height, float room_size);
    void create_rooms() override;
    void set_rooms_sides() override;
    void create_context(float dynamic_objects_ratio) override;
    void create_state(IStateManager* state_manager, std::string window_title) override;
    void set_all_to_state() override;
    std::unique_ptr<GameState> get_game() override { return std::move(m_game_state); };
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
    GameBuilderDirector(std::unique_ptr<IGameBuilder> ptr_builder, const std::string& window_title,
                        float dynamic_objects_ratio);
    std::unique_ptr<GameState> build(IStateManager* state_manager);
private:
    float m_dynamic_objects_ratio;
    std::string m_window_title;
    std::unique_ptr<IGameBuilder> m_ptr_builder;
};