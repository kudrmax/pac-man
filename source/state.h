#include <SFML/Graphics.hpp>

class IStateManager;

class IState {
public:
    IState(IStateManager* state_manager);
    bool do_step();
protected:
    IStateManager* m_state_manager;
};

class IStateManager {
public:
    void set_next_state(IState* state);
};


class Application : public IStateManager {
public:
    void set_next_state(IState* state);
    int run();
    void apply_deffer_state_change();
private:
    void event_handling();
    void update();
    void render();
private:
    IState* m_ptr_state_current;
    IState* m_ptr_state_next;
};


class IWindowKeeper{
public:
//    IWindowKeeper(type mode, std::string title);
protected:
    void event_handling();
    void update();
    void render();
protected:
    sf::RenderWindow m_window;
};

class SelectLevelState : public IState, public IWindowKeeper {
public:
//    SelectLevelState(type state_manager, type window_title);
private:
//    Menu m_menu;
};

class ExitState : public IState {
public:
    bool do_step();
};

class GameState : public IState, public IWindowKeeper {
public:
    GameState(IStateManager* state_manager, std::string window_title);
//    void set_maze(Maze maze);
//    void set_context(GameContext context);
private:
//    void process_key_pressed(code);
//    void process_event(IGameEvent* ptr_event);
private:
//    ContextManager m_context_manager;
//    Maze m_maze;
};