#include "pch.hpp"
#include "game.hpp"
#include "config.hpp"
#include "assetManager.hpp"

// #############################################################################
//                           Functions(Internal)
// #############################################################################
void render_entity(const entt::registry& reg, const entt::entity entity)
{
  const Sprite& sprite = reg.get<Sprite>(entity); 
  const Position& position = reg.get<Position>(entity);

  DrawTextureRec(*sprite.texture, sprite.rect, {position.x, position.y}, WHITE);
}

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
    reg.emplace<Position>(background, Position{0, 0});
  }
  
  // init player
  entt::entity &player = gameState->player;
  player = reg.create();
  Sprite& playerSprite = reg.emplace<Sprite>(player, get_sprite(SPRITE_PLAYER_UP));
  Position& playerPos = reg.emplace<Position>(player, 100, 100);
  Velocity& playerVel = reg.emplace<Velocity>(player, 2, 2);

  // init gameCamera
  Camera2D &gameCamera = gameState->gameCamera;
  {
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
  entt::entity &player = gameState->player;
  Position &playerPos = reg.get<Position>(player);
  Velocity &playerVel = reg.get<Velocity>(player);
  Sprite &playerSprite = reg.get<Sprite>(player);
  {
    if (IsKeyDown(KEY_W)) 
    {
      playerPos.y -= playerVel.y; 
      playerSprite = get_sprite(SPRITE_PLAYER_UP);
    }
    if (IsKeyDown(KEY_S)) 
    {
      playerPos.y += playerVel.y; 
      playerSprite = get_sprite(SPRITE_PLAYER_DOWN);
    }
    if (IsKeyDown(KEY_A)) 
    {
      playerPos.x -= playerVel.x; 
      playerSprite = get_sprite(SPRITE_PLAYER_LEFT);
    }
    if (IsKeyDown(KEY_D)) 
    {
      playerPos.x += playerVel.x; 
      playerSprite = get_sprite(SPRITE_PLAYER_RIGHT);
    }
  }

  // update camera
  Camera2D &gameCamera = gameState->gameCamera;
  {
    gameCamera.target = {playerPos.x, playerPos.y};
  }
}

void game_render(GameState *gameState)
{
  const entt::registry &reg = gameState->reg;
  
  BeginMode2D(gameState->gameCamera);
  {
    // render background
    render_entity(reg, gameState->background);

    // render player
    render_entity(reg, gameState->player);
  }
  EndMode2D();
}

void game_cleanup(GameState *gameState)
{
}
