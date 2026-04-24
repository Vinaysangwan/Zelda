#include "pch.hpp"
#include "game.hpp"
#include "config.hpp"

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

  // init textures
  Texture2D &playerTexture = gameState->playerTexture;
  {
    // background
    gameState->backgroundTexture = LoadTexture("assets/textures/background.png");

    // player
    playerTexture = LoadTexture("assets/textures/player-sheet.png");
  }
  
  // init player
  entt::entity &player = gameState->player;
  player = reg.create();
  Sprite& playerSprite = reg.emplace<Sprite>(player, &playerTexture, Rectangle{12, 0, 12, 18});
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
  {
    if (IsKeyDown(KEY_W)) playerPos.y -= playerVel.y;
    if (IsKeyDown(KEY_S)) playerPos.y += playerVel.y;
    if (IsKeyDown(KEY_A)) playerPos.x -= playerVel.x;
    if (IsKeyDown(KEY_D)) playerPos.x += playerVel.x;
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
    DrawTexture(gameState->backgroundTexture, 0, 0, WHITE);

    // render player
    render_entity(reg, gameState->player);
  }
  EndMode2D();
}

void game_cleanup(GameState *gameState)
{
  // unload textures
  UnloadTexture(gameState->backgroundTexture);
  UnloadTexture(gameState->playerTexture);
}
