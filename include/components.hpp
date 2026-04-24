#pragma once

#include <raylib.h>

struct Position
{
  float x;
  float y;
};

struct Velocity
{
  float x;
  float y;
};

struct Sprite
{
  Texture2D* texture;
  Rectangle rect;

  Sprite(Texture2D *texture)
  : texture(texture), rect{0, 0, static_cast<float>(texture->width), static_cast<float>(texture->height)}
  {}

  Sprite(Texture2D *texture, const Rectangle &rect)
  : texture(texture), rect(rect)
  {}
};
