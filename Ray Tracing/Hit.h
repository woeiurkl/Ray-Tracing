#pragma once

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

class Object;

class Hit
{
public:
    float d; 
    glm::vec3 point;
    glm::vec3 normal;
    glm::vec2 uv;

    std::shared_ptr<Object> obj;
};