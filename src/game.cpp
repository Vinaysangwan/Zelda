#include "pch.hpp"
#include "game.hpp"
#include "config.hpp"
#include "assetManager.hpp"
#include "systems.hpp"
#include "physics.hpp"

// #############################################################################
//                           Functions
// #############################################################################
void game_init(GameState *gameState)
{
  entt::registry& reg = gameState->reg;

  // init debug
  {
    gameState->debug = true;
  }

  // init physics world
  {
    b2SetLengthUnitsPerMeter(PIXEL_PER_METER);
    
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0, 500.0f};
    gameState->physicsWorldId = b2CreateWorld(&worldDef);
  }

  // init background
  {
    entt::entity &background = gameState->background;
    
    background = reg.create();
    reg.emplace<Sprite>(background, get_sprite(SPRITE_BACKGROUND));
    reg.emplace<BackgroundLayerTag>(background);
    reg.emplace<Transform2D>(background);
  }
  
  // init player
  {
    entt::entity &player = gameState->player;

    player = reg.create();
    const Sprite& sprite = reg.emplace<Sprite>(player, get_sprite(SPRITE_PLAYER_DOWN));
    reg.emplace<GameLayerTag>(player);
    const Transform2D& trans = reg.emplace<Transform2D>(player, Transform2D{
      .pos = {100, 100},
      .scale = {4, 4}
    });

    reg.emplace<PhysicsBody>(player, create_rect_body(
      gameState->physicsWorldId, b2_dynamicBody, {trans.pos.x, trans.pos.y},
      sprite.rect.width * trans.scale.x, sprite.rect.height * trans.scale.y
    ));
  }

  // init ground
  {
    entt::entity ground = reg.create();
    // reg.emplace<GameLayerTag>(ground);
    // const Transform2D &trans = reg.emplace<Transform2D>(ground, Transform2D{
    //   .pos = {100, 300},
    // });

    reg.emplace<PhysicsBody>(ground, create_rect_body(
      gameState->physicsWorldId, b2_staticBody, {100, 400},
      300, 100
    ));
  }

  // init game camera
  {
    Camera2D &gameCamera = gameState->gameCamera;

    Transform2D &playerTransform = reg.get<Transform2D>(gameState->player);

    gameCamera.offset = {
      .x = WINDOW_WIDTH / 2.0f,
      .y = WINDOW_HEIGHT / 2.0f
    };
    gameCamera.target = playerTransform.pos;
    gameCamera.zoom = 1.0f;
  }
}

void game_handle_key_pressed(GameState *gameState)
{
  if (IsKeyPressed(KEY_D))
  {
    gameState->debug = !gameState->debug;
  }

  // jump
  if (IsKeyPressed(KEY_SPACE))
  {
    PhysicsBody &body = gameState->reg.get<PhysicsBody>(gameState->player);
    float jumpForce = -40000 * PIXEL_PER_METER;
    b2Body_ApplyLinearImpulseToCenter(body.bodyId, {0, jumpForce}, true);
  }
}

void game_update(GameState *gameState, float dt)
{
  entt::registry &reg = gameState->reg;

  // update player
  {
    entt::entity &player = gameState->player;
    Sprite& playerSprite = reg.get<Sprite>(player);
    PhysicsBody &body = reg.get<PhysicsBody>(player);

    float forwardForce = 40000 * PIXEL_PER_METER;

    if (IsKeyDown(KEY_UP))
    {
      playerSprite = get_sprite(SPRITE_PLAYER_UP);
    }
    if (IsKeyDown(KEY_DOWN))
    {
      playerSprite = get_sprite(SPRITE_PLAYER_DOWN);
    }
    if (IsKeyDown(KEY_LEFT))
    {
      playerSprite = get_sprite(SPRITE_PLAYER_LEFT);
      b2Body_ApplyForceToCenter(body.bodyId, {-forwardForce, 0}, true);
    }
    if (IsKeyDown(KEY_RIGHT))
    {
      playerSprite = get_sprite(SPRITE_PLAYER_RIGHT);
      b2Body_ApplyForceToCenter(body.bodyId, {forwardForce, 0}, true);
    }

    b2Vec2 position = b2Body_GetPosition(body.bodyId);
    b2Rot rotation = b2Body_GetRotation(body.bodyId);
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
  }

  // update physics world
  b2World_Step(gameState->physicsWorldId, dt, 4);

  // update entity physics
  update_entity_physics(reg);

  // update camera
  {
    Camera2D &gameCamera = gameState->gameCamera;
    Vector2 &playerPos = reg.get<Transform2D>(gameState->player).pos;

    gameCamera.target = playerPos;
  }
}

void game_render(GameState *gameState)
{
  entt::registry &reg = gameState->reg;
  
  BeginMode2D(gameState->gameCamera);
  {
    // render entities
    render_entities(reg);

    if (gameState->debug)
    {
      render_debug_colliders(reg);
    }
  }
  EndMode2D();
}

void game_cleanup(GameState *gameState)
{
  // clear entity register
  gameState->reg.clear();
}
