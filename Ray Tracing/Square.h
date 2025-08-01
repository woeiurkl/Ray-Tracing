#pragma once

#include "Triangle.h"

class Square : public Object
{
public:
    Triangle triangle1, triangle2;

    Square(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec2 uv0 = glm::vec2(0.0f), glm::vec2 uv1 = glm::vec2(0.0f), glm::vec2 uv2 = glm::vec2(0.0f), glm::vec2 uv3 = glm::vec2(0.0f));

    virtual Hit CheckRayCollision(Ray& ray);
};