#include "physics.hpp"

// #############################################################################
//                           Functions
// #############################################################################
PhysicsBody create_rect_body(b2WorldId worldId, b2BodyType type, b2Vec2 pos, float width, float height)
{
  // body def
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = type;
  bodyDef.position = pos;

  // body id
  b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

  // shape def
  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 1.0f;
  shapeDef.material.friction = 0.1f;

  // polygon
  b2Polygon polygon = b2MakeBox(width * 0.5f, height * 0.5f);
  b2CreatePolygonShape(bodyId, &shapeDef, &polygon);

  return {
    .bodyId = bodyId,
    .size = {width, height}
  };
}
