#pragma once

#include <raylib.h>
#include <box2d/box2d.h>

// #############################################################################
//                           Tags
// #############################################################################
struct BackgroundLayerTag {};
struct GameLayerTag {};
struct UILayerTag {};

// #############################################################################
//                           Components
// #############################################################################
struct Transform2D
{
  Vector2 pos = {0.0f, 0.0f};
  Vector2 scale = {1.0f, 1.0f};
  float rot = 0.0f;
};

struct Velocity
{
  float x = 0.0f;
  float y = 0.0f;
};

struct PhysicsBody
{
  b2BodyId bodyId;
  Vector2 size;
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
