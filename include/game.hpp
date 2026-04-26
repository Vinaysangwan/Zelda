#pragma once

#include "components.hpp"
#include <entt.hpp>

// #############################################################################
//                           Structs
// #############################################################################
struct GameState
{
  bool debug;
  
  entt::registry reg;

  // camera
  Camera2D gameCamera;

  // physics world
  b2WorldId physicsWorldId;
  
  // entities
  entt::entity background;
  entt::entity player;
};

// #############################################################################
//                           Functions
// #############################################################################
void game_init(GameState* gameState);
void game_handle_key_pressed(GameState *gameState);
void game_update(GameState* gameState, float dt);
void game_render(GameState* gameState);
void game_cleanup(GameState* gameState);
