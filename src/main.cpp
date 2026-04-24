#include "pch.hpp"
#include "config.hpp"
#include "game.hpp"

// #############################################################################
//                           Functions
// #############################################################################
int main()
{
  // init window
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Zelda");
  SetTargetFPS(FPS);

  // init game
  GameState gameState = {};
  game_init(&gameState);

  // main game loop
  float upsTimer = 0;
  while(!WindowShouldClose())
  {
    // get delta time
    float delta = GetFrameTime();
    
    // update
    upsTimer += delta;
    while (upsTimer >= UPS_TIME)
    {
      upsTimer -= UPS_TIME;
      game_update(&gameState, UPS_TIME);
    }
    
    // render
    BeginDrawing();
    ClearBackground(BLACK);
    {
      game_render(&gameState);
      DrawFPS(10, 10);
    }
    EndDrawing();
  }

  // cleanup
  game_cleanup(&gameState);
  CloseWindow();
}
