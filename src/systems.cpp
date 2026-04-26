#include "pch.hpp"
#include "systems.hpp"

// #############################################################################
//                           Internal Functions
// #############################################################################
template <typename LayerTag>
void render_layer(entt::registry &reg)
{
  auto view = reg.view<const Sprite, const Transform2D, const LayerTag>();

  for (auto&& [entity, sprite, trans] : view.each())
  {
    float width = sprite.rect.width * trans.scale.x;
    float height = sprite.rect.height * trans.scale.y;
    
    DrawTexturePro(*sprite.texture, sprite.rect, 
      {trans.pos.x, trans.pos.y, width, height},
      {width * 0.5f, height * 0.5f},
      trans.rot, WHITE
    );
  }
}

// #############################################################################
//                           Functions
// #############################################################################
void render_entities(entt::registry &reg)
{
  render_layer<BackgroundLayerTag>(reg);
  render_layer<GameLayerTag>(reg);
  render_layer<UILayerTag>(reg);
}

void render_debug_colliders(entt::registry &reg)
{
  auto view = reg.view<PhysicsBody>();

  for (auto&& [entity, body] : view.each())
  {
    b2Vec2 pos = b2Body_GetPosition(body.bodyId);
    b2Rot rotation = b2Body_GetRotation(body.bodyId);
    float radian = b2Rot_GetAngle(rotation);
    
    DrawRectanglePro({pos.x, pos.y, body.size.x, body.size.y}, 
      {body.size.x * 0.5f, body.size.y * 0.5f}, RAD2DEG * radian, Fade(RED, 0.2f));

    // DrawRectangleLinesEx({pos.x - body.size.x * 0.5f, pos.y - body.size.y * 0.5f, body.size.x, body.size.y}, 2, RED);
  }
}

void move_entities(entt::registry &reg)
{
  auto view = reg.view<Transform2D, const Velocity>();

  for (auto&& [entity, trans, vel] : view.each())
  {
    trans.pos.x += vel.x;
    trans.pos.y += vel.y;
  }
}

void update_entity_physics(entt::registry &reg)
{
  auto view = reg.view<const PhysicsBody, Transform2D>();

  for (auto&& [entity, body, trans] : view.each())
  {
    b2Vec2 pos = b2Body_GetPosition(body.bodyId);
    b2Rot rotation = b2Body_GetRotation(body.bodyId);
    float radian = b2Rot_GetAngle(rotation);

    trans.pos = {pos.x, pos.y};
    trans.rot = RAD2DEG * radian;
  }
}
