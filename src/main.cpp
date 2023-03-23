#include <vector>
#include <fstream>

#include "raylib.h"
#include "raymath.h"
#include <nlohmann/json.hpp>
#include <iostream>

#define MAPS_PATH "/Users/martonszuts/Code/C++/RayLib/star-breaker/maps/"

bool CheckCollisionCircleLine(Vector2 circleCenter, float radius, Vector2 lineStart, Vector2 lineEnd)
{
    Vector2 lineDiff = Vector2Subtract(lineEnd, lineStart);
    Vector2 circleToLineStart = Vector2Subtract(circleCenter, lineStart);

    float t = Vector2DotProduct(circleToLineStart, lineDiff) / Vector2DotProduct(lineDiff, lineDiff);

    if (t < 0.0f)
        t = 0.0f;
    else if (t > 1.0f)
        t = 1.0f;

    Vector2 projection = Vector2Add(lineStart, Vector2Scale(lineDiff, t));
    Vector2 circleToProjection = Vector2Subtract(circleCenter, projection);

    return (Vector2LengthSqr(circleToProjection) <= radius * radius);
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    std::ifstream f(MAPS_PATH + std::string("test.json"));
    if (!f) {
        std::cerr << "Failed to open file: " << std::strerror(errno) << std::endl;
        return 1;
    }
    nlohmann::json data;
    try {
        data = nlohmann::json::parse(f);
        std::cout << data.dump() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        return 1;
    }

    InitWindow(screenWidth, screenHeight, "Ball Bouncing Example with Shapes");

    Vector2 ballPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
    Vector2 ballSpeed = {2.0f, 3.0f};
    float ballRadius = 10.0f;

    // Define shapes
    Rectangle rect = {100, 100, 200, 100};
    Vector2 circlePosition = {400, 400};
    float circleRadius = 40.0f;

    // Points for the triangle
    Vector2 triangleA = {100, 10};
    Vector2 triangleB = {10, 100};
    Vector2 triangleC = {100, 100};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Bounce from window borders
        if (ballPosition.x <= ballRadius || ballPosition.x >= screenWidth - ballRadius) {
            ballSpeed.x *= -1;
        }
        if (ballPosition.y <= ballRadius || ballPosition.y >= screenHeight - ballRadius) {
            ballSpeed.y *= -1;
        }

        // Bounce off shapes
        // Rectangle
        if (CheckCollisionCircleRec(ballPosition, ballRadius, rect)) {
            // Determine which side of the rectangle the ball hit
            float prevX = ballPosition.x - ballSpeed.x;
            float prevY = ballPosition.y - ballSpeed.y;

            if (prevX - ballRadius < rect.x + rect.width && prevX + ballRadius > rect.x) {
                ballSpeed.y *= -1;
            } else {
                ballSpeed.x *= -1;
            }
        }

        // Circle
        if (CheckCollisionCircles(ballPosition, ballRadius, circlePosition, circleRadius)) {
            Vector2 normal = Vector2Subtract(ballPosition, circlePosition);
            normal = Vector2Normalize(normal);
            float speedLength = Vector2Length(ballSpeed);
            ballSpeed = Vector2Scale(normal, speedLength);
        }

        // Triangle
        // Triangle
        Vector2 edgeAB = Vector2Subtract(triangleB, triangleA);
        Vector2 edgeBC = Vector2Subtract(triangleC, triangleB);
        Vector2 edgeCA = Vector2Subtract(triangleA, triangleC);

        bool collisionAB = CheckCollisionCircleLine(ballPosition, ballRadius, triangleA, triangleB);
        bool collisionBC = CheckCollisionCircleLine(ballPosition, ballRadius, triangleB, triangleC);
        bool collisionCA = CheckCollisionCircleLine(ballPosition, ballRadius, triangleC, triangleA);

        Vector2 normal = {0};

        if (collisionAB) {
            normal = {-edgeAB.y, edgeAB.x};
        } else if (collisionBC) {
            normal = {-edgeBC.y, edgeBC.x};
        } else if (collisionCA) {
            normal = {-edgeCA.y, edgeCA.x};
        }

        if (collisionAB || collisionBC || collisionCA) {
            normal = Vector2Normalize(normal);
            float dot = 2 * (ballSpeed.x * normal.x + ballSpeed.y * normal.y);
            ballSpeed.x -= dot * normal.x;
            ballSpeed.y -= dot * normal.y;
        }

        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawCircleV(ballPosition, ballRadius, DARKBLUE);
        DrawRectangleRec(rect, RED);
        DrawCircleV(circlePosition, circleRadius, GREEN);
        DrawTriangle(triangleA, triangleB, triangleC, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
