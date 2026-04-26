#pragma once

#include "components.hpp"
#include <entt.hpp>

// #############################################################################
//                           Functions
// #############################################################################
void render_entities(entt::registry &reg);
void render_debug_colliders(entt::registry &reg);
void move_entities(entt::registry &reg);
void update_entity_physics(entt::registry &reg);
