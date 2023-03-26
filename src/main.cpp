#include <vector>
#include <fstream>

#include "raylib.h"
#include "raymath.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include "utils.h"
#include "logger.h"
#include "GameScene.hpp"

int main()
{
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
