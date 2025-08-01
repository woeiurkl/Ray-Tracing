#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Hit.h"
#include "Ray.h"
#include "Texture.h"

//namespace hlab
//{
    //using namespace glm;

    class Object
    {
    public:
        // Material
        glm::vec3 amb = glm::vec3(0.0f);  // Ambient
        glm::vec3 dif = glm::vec3(0.0f);  // Diffuse
        glm::vec3 spec = glm::vec3(0.0f); // Specular
        float alpha = 10.0f;
        float reflection = 0.0;
        float transparency = 0.0;

        std::shared_ptr<Texture> ambTexture;
        std::shared_ptr<Texture> difTexture;

        Object(const glm::vec3& color = { 1.0f, 1.0f, 1.0f })
            : amb(color), dif(color), spec(color)
        {
        }

        virtual Hit CheckRayCollision(Ray& ray) = 0;
    };
//}