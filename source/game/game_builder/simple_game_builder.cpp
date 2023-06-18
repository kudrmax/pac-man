#include "simple_game_builder.h"
#include "../../config.h"
#include <algorithm>


void SimpleGameBuilder::create_rooms() {
    size_t count_of_rooms_x = m_width / m_room_size - 2;
    size_t count_of_rooms_y = m_height / m_room_size - 2;
    if (count_of_rooms_x % 2 == 0) ++count_of_rooms_x;
    if (count_of_rooms_y % 2 == 0) ++count_of_rooms_y;
    auto start_x = (m_width - count_of_rooms_x * m_room_size) / 2.0f + m_room_size / 2.0f;
    auto start_y = (m_height - count_of_rooms_y * m_room_size + m_room_size) / 2.0f;

    std::vector<std::unique_ptr<Room>> row_v;
    for (size_t i_y = 0; i_y < count_of_rooms_y; ++i_y) {
        for (size_t i_x = 0; i_x < count_of_rooms_x; ++i_x) {
                auto room = std::make_unique<Room>(m_room_size);
                room->set_position({ start_x + i_x * m_room_size, start_y + i_y * m_room_size });
                row_v.emplace_back(std::move(room));
        }
        m_rooms.push_back(std::move(row_v));
        row_v.clear();
    }
}