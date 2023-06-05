#include "entity.h"
#include "side.h"

void PacMan::move(Room::Direction direction) {
    auto side = m_location->get_side(direction);
    side->enter(this);
}
