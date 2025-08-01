#pragma once
#include "Object.h"

//namespace hlab
//{
    //using namespace glm;

    class Sphere : public Object
    {
    public:
        glm::vec3 center;
        float radius;

        Sphere(const glm::vec3& center, const float radius, const glm::vec3& color = glm::vec3(1.0f))
            : center(center), radius(radius), Object(color)
        {
        }

        // Wikipedia Line–sphere intersection
        // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
        Hit CheckRayCollision(Ray& ray);
    };
//}
