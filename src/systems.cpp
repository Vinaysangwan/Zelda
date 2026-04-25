#include "pch.hpp"
#include "systems.hpp"

// #############################################################################
//                           Internal Functions
// #############################################################################
template <typename LayerTag>
void render_layer(entt::registry &reg)
{
  auto view = reg.view<const Sprite, const Position, const LayerTag>();

  for (auto&& [entity, sprite, pos] : view.each())
  {
    DrawTextureRec(*sprite.texture, sprite.rect, {pos.x, pos.y}, WHITE);
  }
}

// #############################################################################
//                           Functions
// #############################################################################
// * Old Render Code
// void render_system(entt::registry &reg)
// {
//   auto view = reg.view<Sprite, Position, RenderLayer>();

//   std::vector<entt::entity> entities(view.begin(), view.end());

//   std::sort(entities.begin(), entities.end(), 
//   [&](entt::entity a, entt::entity b)
//   {
//     return reg.get<RenderLayer>(a).layer < reg.get<RenderLayer>(b).layer;
//   });

//   for (entt::entity entity : entities)
//   {
//     Sprite& sprite = reg.get<Sprite>(entity);
//     Position& pos = reg.get<Position>(entity);

//     DrawTextureRec(*sprite.texture, sprite.rect, {pos.x, pos.y}, WHITE);
//   }
// }

void render_system(entt::registry &reg)
{
  render_layer<BackgroundLayerTag>(reg);
  render_layer<GameLayerTag>(reg);
  render_layer<UILayerTag>(reg);
}

void movement_system(entt::registry &reg)
{
  auto view = reg.view<Position, const Velocity>();

  for (auto&& [entity, pos, vel] : view.each())
  {
    pos.x += vel.x;
    pos.y += vel.y;
  }
}
