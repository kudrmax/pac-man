#pragma once

#include "../state/state.h"

struct ISelectCommand {
    virtual void execute() = 0;
    virtual ~ISelectCommand() = default;
};

struct IChangeStateCommand : public ISelectCommand {
    IChangeStateCommand(IStateManager& state_manager) : m_state_manager(&state_manager) {}; // СПОРНО
protected:
    IStateManager* m_state_manager;
};

struct ExitCommand : public IChangeStateCommand {
    using IChangeStateCommand::IChangeStateCommand;
    void execute();
};

struct GameCommand : public IChangeStateCommand {
    using IChangeStateCommand::IChangeStateCommand;
    void execute();
};