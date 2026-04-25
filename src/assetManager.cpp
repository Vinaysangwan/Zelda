#include "assetManager.hpp"

// #############################################################################
//                           Textures
// #############################################################################
static Texture2D TEXTURES[TEXTURE_COUNT];
static Sprite SPRITES[SPRITE_COUNT];

void load_sprites()
{
  // player
  SPRITES[SPRITE_PLAYER_DOWN]   = Sprite(get_texture(TEXTURE_PLAYER), Rectangle{12, 0, 12, 18});
  SPRITES[SPRITE_PLAYER_LEFT]   = Sprite(get_texture(TEXTURE_PLAYER), Rectangle{12, 18, 12, 18});
  SPRITES[SPRITE_PLAYER_RIGHT]  = Sprite(get_texture(TEXTURE_PLAYER), Rectangle{12, 2 * 18, 12, 18});
  SPRITES[SPRITE_PLAYER_UP]     = Sprite(get_texture(TEXTURE_PLAYER), Rectangle{12, 3 * 18, 12, 18});

  SPRITES[SPRITE_BACKGROUND]    = Sprite(get_texture(TEXTURE_BACKGROUND));
}

void textures_load()
{
  // textures
  TEXTURES[TEXTURE_PLAYER] = LoadTexture("assets/textures/player-sheet.png");
  TEXTURES[TEXTURE_BACKGROUND] = LoadTexture("assets/textures/background.png");

  // sprites
  load_sprites();
}

void textures_unload()
{
  for (Texture2D &tex : TEXTURES)
  {
    UnloadTexture(tex);
  }

  for (Sprite &sprite : SPRITES)
  {
    sprite.texture = nullptr;
  }
}

Texture2D *get_texture(TextureID textureID)
{
  return &TEXTURES[textureID];
}

const Sprite &get_sprite(SpriteID spriteID)
{
  return SPRITES[spriteID];
}
