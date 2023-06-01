#pragma once

#include "../i_state.h"
#include "../i_window.h"
#include "menu.h"


class IState;
class IWindowKeeper;

class SelectState : public IState, public IWindowKeeper {
public:
    SelectState(IStateManager* state_manager, const std::string& window_title);
    bool do_step() override;
    void event_handling() override;
    void update() override;
    void render() override;
private:
    Menu m_menu;
};