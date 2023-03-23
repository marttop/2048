/*
** star-breaker
** File description:
** utils
*/

#ifndef UTILS_H_
#define UTILS_H_

#include "raylib.h"
#include "raymath.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>

bool CheckCollisionCircleLine(Vector2 circleCenter, float radius, Vector2 lineStart, Vector2 lineEnd);

#endif /* !UTILS_H_ */
