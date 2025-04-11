#include <cstdint>
#include <raylib.h>
#include <string>

#include "graphics/pokeemerald.h"

extern "C"
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
  __declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance =
    0x00000001;
}

int
main()
{
  std::string window_title = "pokeport";
  uint32_t window_width = 240;
  uint32_t window_height = 160;
  uint32_t scale_factor = 4;

  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(window_width * scale_factor,
             window_height * scale_factor,
             window_title.c_str());

  Image image = {
    .data = POKEEMERALD_DATA,
    .width = POKEEMERALD_WIDTH,
    .height = POKEEMERALD_HEIGHT,
    .mipmaps = 1,
    .format = POKEEMERALD_FORMAT,
  };

  Texture2D texture = LoadTextureFromImage(image);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTextureEx(texture, Vector2{}, 0.0f, (float)scale_factor, WHITE);

    EndDrawing();
  }

  UnloadTexture(texture);

  CloseWindow();
}