#include "utils.h"

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

nlohmann::json getJsonFromFile(const std::string &filepath)
{
    std::ifstream f(filepath);
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
}