#pragma once

#include "Object.h"

//namespace hlab
//{
    //using namespace glm;

    class Triangle : public Object
    {
    public:
        glm::vec3 v0, v1, v2;
        glm::vec2 uv0, uv1, uv2; // 뒤에서 텍스춰 좌표계로 사용

    public:
        Triangle()
            : v0(glm::vec3(0.0f)), v1(glm::vec3(0.0f)), v2(glm::vec3(0.0f)), uv0(glm::vec2(0.0f)), uv1(glm::vec2(0.0f)), uv2(glm::vec2(0.0f))
        {
        }

        Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec2 uv0 = glm::vec2(0.0f), glm::vec2 uv1 = glm::vec2(0.0f), glm::vec2 uv2 = glm::vec2(0.0f))
            : v0(v0), v1(v1), v2(v2), uv0(uv0), uv1(uv1), uv2(uv2)
        {
        }

        virtual Hit CheckRayCollision(Ray& ray);

        // 참고: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
        bool IntersectRayTriangle(const glm::vec3& orig, const glm::vec3& dir,
            const glm::vec3& v0, const glm::vec3& v1,
            const glm::vec3& v2, glm::vec3& point, glm::vec3& faceNormal,
            float& t, float& w0, float& w1);
    };
//} // namespace hlab