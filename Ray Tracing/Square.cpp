#include "Square.h"

Square::Square(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
    glm::vec2 uv0, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3)
{
    triangle1.uv0 = uv0;
    triangle1.uv1 = uv1;
    triangle1.uv2 = uv2;

    triangle2.uv0 = uv0;
    triangle2.uv1 = uv2;
    triangle2.uv2 = uv3;
}

Hit Square::CheckRayCollision(Ray& ray)
{
    auto hit1 = triangle1.CheckRayCollision(ray);
    auto hit2 = triangle2.CheckRayCollision(ray);

    if (hit1.d >= 0.0f && hit2.d >= 0.0f)
    {
        return hit1.d < hit2.d ? hit1 : hit2;
    }
    else if (hit1.d >= 0.0f)
    {
        return hit1;
    }
    else
    {
        return hit2;
    }
}