/*
** star-breaker
** File description:
** utils
*/

#ifndef UTILS_H_
#define UTILS_H_

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 920
#define MAPS_PATH "/Users/martonszuts/Code/C++/RayLib/star-breaker/maps/"

#include "raylib.h"
#include "raymath.h"
#include "logger.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

bool CheckCollisionCircleLine(Vector2 circleCenter, float radius, Vector2 lineStart, Vector2 lineEnd);

#endif /* !UTILS_H_ */
