#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

class Light
{
public:
    glm::vec3 pos;
    float intensity = 1.0f;
};