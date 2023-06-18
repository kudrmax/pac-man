#pragma once

#include "game_builder_with_holes.h"

class SimpleGameBuilder : public GameBuilderWithHoles {
public:
    using GameBuilderWithHoles::GameBuilderWithHoles;
    void create_rooms() override;
};