#pragma once

#include "game_contex.h"
#include <memory>

struct IGameEvent {
    virtual void handle(std::unique_ptr<GameContext> context) = 0;
    virtual ~IGameEvent() = default;
};

struct WinGame : public IGameEvent {
    void handle(std::unique_ptr<GameContext> context) override {}
};

struct LostGame : public IGameEvent {
    void handle(std::unique_ptr<GameContext> context) override {}
};

struct DeleteStaticEntity : public IGameEvent {
    DeleteStaticEntity(std::unique_ptr<IStaticEntity> ptr_entity);
    void handle(std::unique_ptr<GameContext> context) override {}
private:
    std::unique_ptr<IStaticEntity> m_ptr_entity;
};