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
    reg.emplace<Position>(background, 0, 0);
    reg.emplace<RenderLayer>(background, 0);
  }
  
  // init player
  {
    entt::entity &player = gameState->player;

    player = reg.create();
    reg.emplace<Sprite>(player, get_sprite(SPRITE_PLAYER_DOWN));
    reg.emplace<Position>(player, 100, 100);
    reg.emplace<Velocity>(player, 0, 0);
    reg.emplace<RenderLayer>(player, 1);
  }

  // init example entity
  {
    entt::entity example = reg.create();
    reg.emplace<Sprite>(example, get_sprite(SPRITE_PLAYER_UP));
    reg.emplace<Position>(example, 100, 10);
    reg.emplace<Velocity>(example, 1, 1);
    reg.emplace<RenderLayer>(example, 1);
  }

  // init gameCamera
  {
    Camera2D &gameCamera = gameState->gameCamera;

    Sprite &playerSprite = reg.get<Sprite>(gameState->player);
    Position &playerPos = reg.get<Position>(gameState->player);

    gameCamera.offset = {
      .x = (WINDOW_WIDTH - playerSprite.rect.width) / 3, 
      .y = (WINDOW_HEIGHT - playerSprite.rect.height) / 2
    };
    gameCamera.target = {playerPos.x, playerPos.y};
    gameCamera.zoom = 4.0f;
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
    Position &examplePos = reg.get<Position>(entt::entity(2));

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
    Position &playerPos = reg.get<Position>(gameState->player);

    gameCamera.target = {playerPos.x, playerPos.y};
  }
}

void game_render(GameState *gameState)
{
  entt::registry &reg = gameState->reg;
  
  BeginMode2D(gameState->gameCamera);
  {
    // render entity
    render_system(reg);
  }
  EndMode2D();
}

void game_cleanup(GameState *gameState)
{
  // clear entity register
  gameState->reg.clear();
}
