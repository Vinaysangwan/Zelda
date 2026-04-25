#pragma once

#include <raylib.h>

struct Position
{
  float x = 0.0f;
  float y = 0.0f;
};

struct Velocity
{
  float x = 0.0f;
  float y = 0.0f;
};

struct Sprite
{
  Texture2D* texture;
  Rectangle rect;

  Sprite()
  {} 
  
  Sprite(Texture2D *texture)
    : texture(texture), rect{0, 0, static_cast<float>(texture->width), static_cast<float>(texture->height)}
  {}

  Sprite(Texture2D *texture, const Rectangle &rect)
    : texture(texture), rect(rect)
  {}
};

struct RenderLayer
{
  int layer;
};
