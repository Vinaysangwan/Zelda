#include "pch.hpp"
#include "game.hpp"
#include "config.hpp"
#include "assetManager.hpp"
#include "systems.hpp"

// #############################################################################
//                           Functions
// #############################################################################
void game_init(GameState *gameState)
{
  entt::registry& reg = gameState->reg;

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
    reg.emplace<Sprite>(player, get_sprite(SPRITE_PLAYER_DOWN));
    reg.emplace<GameLayerTag>(player);
    reg.emplace<Transform2D>(player, Transform2D{
      .pos = {100, 100},
      .scale = {4, 4}
    });
    reg.emplace<Velocity>(player, 2, 2);
  }

  // init example entity
  {
    entt::entity example = reg.create();
    reg.emplace<Sprite>(example, get_sprite(SPRITE_PLAYER_UP));
    reg.emplace<GameLayerTag>(example);
    reg.emplace<Transform2D>(example, Transform2D{
      .pos = {50, 50},
      .scale = {4, 4}
    });
    reg.emplace<Velocity>(example, 1, 1);
  }

  // init bird
  {
    entt::entity bird = reg.create();
    reg.emplace<Sprite>(bird, get_sprite(SPRITE_BIRD));
    reg.emplace<GameLayerTag>(bird);
    reg.emplace<Transform2D>(bird, Transform2D{
      .pos = {100, 100}
    });
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

void game_update(GameState *gameState, float dt)
{
  entt::registry &reg = gameState->reg;

  // update player
  {
    entt::entity &player = gameState->player;
    Sprite& playerSprite = reg.get<Sprite>(player);
    Velocity &playerVel = reg.get<Velocity>(player);

    playerVel.x = 0.0f;
    playerVel.y = 0.0f;
    
    if (IsKeyDown(KEY_W))
    {
      playerVel.y = -2;
      playerSprite = get_sprite(SPRITE_PLAYER_UP);
    }
    if (IsKeyDown(KEY_S))
    {
      playerVel.y = 2;
      playerSprite = get_sprite(SPRITE_PLAYER_DOWN);
    }
    if (IsKeyDown(KEY_A))
    {
      playerVel.x = -2;
      playerSprite = get_sprite(SPRITE_PLAYER_LEFT);
    }
    if (IsKeyDown(KEY_D))
    {
      playerVel.x = 2;
      playerSprite = get_sprite(SPRITE_PLAYER_RIGHT);
    }
  }

  // update example
  {
    Velocity &exampleVel = reg.get<Velocity>(entt::entity(2));
    Vector2 &examplePos = reg.get<Transform2D>(entt::entity(2)).pos;

    if (examplePos.x <= 0 || examplePos.x >= 200)
    {
      exampleVel.x *= -1;
    }
    if (examplePos.y <= 0 || examplePos.y >= 100)
    {
      exampleVel.y *= -1;
    }
  }

  // move entities
  movement_system(reg);

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
    render_system(reg);
  }
  EndMode2D();
}

void game_cleanup(GameState *gameState)
{
  // clear entity register
  gameState->reg.clear();
}
