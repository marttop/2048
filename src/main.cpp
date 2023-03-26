#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

#include "GameScene.hpp"
#include "logger.h"
#include "raylib.h"
#include "raymath.h"
#include "utils.h"

int main()
{
#ifdef LOGGING
    spdlog::set_level(spdlog::level::debug);

#else
    SetTraceLogLevel(LOG_NONE);
#endif
    float deltaTime;
    INFO("Starting window {0}*{1}", SCREEN_WIDTH, SCREEN_HEIGHT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(FPS);
    GameScene gameScene;

    while (!WindowShouldClose()) {
        deltaTime = GetFrameTime();
        gameScene.handleEvent();
        gameScene.update(deltaTime);
        BeginDrawing();
        gameScene.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
