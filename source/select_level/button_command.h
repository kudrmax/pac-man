#pragma once

#include "../i_state.h"
#include "../game/game_builder/game_builder_director.h"

struct ISelectCommand {
    virtual void execute() = 0;
    virtual ~ISelectCommand() = default;
};

struct IChangeStateCommand : public ISelectCommand {
    explicit IChangeStateCommand(IStateManager& state_manager) : m_state_manager(state_manager) {};
protected:
    IStateManager& m_state_manager;
};

struct ExitCommand : public IChangeStateCommand {
    using IChangeStateCommand::IChangeStateCommand;
    void execute() override;
};

struct GameCommand : public IChangeStateCommand {
    GameCommand(IStateManager& state_manager, std::unique_ptr<GameBuilderDirector>&& ptr_director)
            : IChangeStateCommand(state_manager), m_ptr_director(std::move(ptr_director)) {};
    void execute() override;
    std::unique_ptr<GameBuilderDirector> m_ptr_director;
};