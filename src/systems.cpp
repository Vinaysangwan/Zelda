#include "pch.hpp"
#include "systems.hpp"

// #############################################################################
//                           Functions
// #############################################################################
void render_system(entt::registry &reg)
{
  auto view = reg.view<Sprite, Position, RenderLayer>();

  std::vector<entt::entity> entities(view.begin(), view.end());

  std::sort(entities.begin(), entities.end(), 
  [&](entt::entity a, entt::entity b)
  {
    return reg.get<RenderLayer>(a).layer < reg.get<RenderLayer>(b).layer;
  });

  // render entities
  for (entt::entity entity : entities)
  {
    Sprite& sprite = reg.get<Sprite>(entity);
    Position& pos = reg.get<Position>(entity);

    DrawTextureRec(*sprite.texture, sprite.rect, {pos.x, pos.y}, WHITE);
  }
}

void movement_system(entt::registry &reg)
{
  auto view = reg.view<Position, Velocity>();

  // move entities
  for (entt::entity entity : view)
  {
    Velocity &vel = reg.get<Velocity>(entity);
    Position &pos = reg.get<Position>(entity);

    pos.x += vel.x;
    pos.y += vel.y;
  }
}
