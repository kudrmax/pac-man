#pragma once

class IStateManager;

class IState {
public:
    explicit IState(IStateManager& state_manager) : m_state_manager(state_manager) {};
    virtual bool do_step() = 0;
    virtual ~IState() = default;
protected:
    IStateManager& m_state_manager;
};