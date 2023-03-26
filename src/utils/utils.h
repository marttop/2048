/*
** star-breaker
** File description:
** utils
*/

#ifndef UTILS_H_
#define UTILS_H_

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define TITLE "2048"
#define FPS 60
#define TILE_PADDING 15.f
#define GRID_RATIO 0.6
#define GRID_PADDING_VERTICAL 70

#include "raylib.h"
#include "raymath.h"
#include "logger.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <map>

bool CheckCollisionCircleLine(Vector2 circleCenter, float radius, Vector2 lineStart, Vector2 lineEnd);

#endif /* !UTILS_H_ */
