#pragma once
//
//#include "state.h"
//#include <memory>
//
//class ISelectCommand {
//public:
//    virtual void execute() = 0;
//    virtual ~ISelectCommand() = default;
//private:
//    std::unique_ptr<ISelectCommand> m_ptr_command;
//};
//
//struct IChangeStateCommand : public ISelectCommand {
//    IChangeStateCommand(IStateManager state_manager){};
//protected:
//    IStateManager* m_state_manager;
//};
//
//struct ExitCommand : public IChangeStateCommand {
//    void execute(){};
//};
//
//struct GameCommand : public IChangeStateCommand{
////    GameCommand(IStateManager state_manager, GameBuilderDirector* ptr_director);
//    GameCommand(IStateManager state_manager, int* ptr_director);
//    void execute(){};
//private:
////    GameBuilderDirector m_ptr_director;
//    int m_ptr_director;
//};