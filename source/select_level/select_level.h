#pragma once

#include "../state/state.h"
#include "../state/window.h"
#include "../draw/menu.h"


class IState;
class IWindowKeeper;

class SelectState : public IState, public IWindowKeeper {
public:
    SelectState(IStateManager& state_manager, const std::string& window_title);
    bool do_step() override;
    void event_handling() override;
    void update() override;
    void render() override;
private:
    Menu m_menu;
};