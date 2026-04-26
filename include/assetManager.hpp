#pragma once

#include <raylib.h>
#include "components.hpp"

// #############################################################################
//                           Textures
// #############################################################################
enum TextureID
{
  TEXTURE_PLAYER,
  TEXTURE_BACKGROUND,
  TEXTURE_BIRD,

  TEXTURE_COUNT
};

enum SpriteID
{
  // player
  SPRITE_PLAYER_DOWN,
  SPRITE_PLAYER_LEFT,
  SPRITE_PLAYER_RIGHT,
  SPRITE_PLAYER_UP,

  // Bird
  SPRITE_BIRD,

  // background
  SPRITE_BACKGROUND,

  SPRITE_COUNT
};

void textures_load();
void textures_unload();
Texture2D *get_texture(TextureID textureID);
const Sprite &get_sprite(SpriteID spriteID);
