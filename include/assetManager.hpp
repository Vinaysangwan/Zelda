#pragma once

#include <raylib.h>
#include "components.hpp"

// #############################################################################
//                           Textures
// #############################################################################
enum SpriteID
{
  // player
  SPRITE_PLAYER_DOWN,
  SPRITE_PLAYER_LEFT,
  SPRITE_PLAYER_RIGHT,
  SPRITE_PLAYER_UP,

  // background
  SPRITE_BACKGROUND,

  SPRITE_COUNT
};

void load_textures();
void unload_textures();
Sprite get_sprite(SpriteID spriteID);
