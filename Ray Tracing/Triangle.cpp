#include "Triangle.h"

Hit Triangle::CheckRayCollision(Ray& ray)
{
    Hit hit = Hit{ -1.0, glm::vec3(0.0), glm::vec3(0.0) };

    glm::vec3 point, faceNormal;
    float t, w0, w1;
    if (IntersectRayTriangle(ray.start, ray.dir, this->v0, this->v1,
        this->v2, point, faceNormal, t, w0, w1))
    {
        hit.d = t;
        hit.point = point; // ray.start + ray.dir * t;
        hit.normal = faceNormal;
        hit.uv = uv0 * w0 + uv1 * w1 + uv2 * (1.0f - w0 - w1);
    }

    return hit;
}

bool Triangle::IntersectRayTriangle(const glm::vec3& orig, const glm::vec3& dir,
    const glm::vec3& v0, const glm::vec3& v1,
    const glm::vec3& v2, glm::vec3& point, glm::vec3& faceNormal,
    float& t, float& w0, float& w1)
{
    faceNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

    if (dot(-dir, faceNormal) < 0.0f)
        return false;

    if (glm::abs(dot(dir, faceNormal)) < 1e-2f)
        return false;

    t = (dot(v0, faceNormal) - dot(orig, faceNormal)) /
        (dot(dir, faceNormal));

    if (t < 0.0f)
        return false;

    point = orig + t * dir;

    const glm::vec3 cross0 = glm::cross(point - v2, v1 - v2);
    const glm::vec3 cross1 = glm::cross(point - v0, v2 - v0);
    const glm::vec3 cross2 = glm::cross(v1 - v0, point - v0);

    if (dot(cross0, faceNormal) < 0.0f)
        return false;
    if (dot(cross1, faceNormal) < 0.0f)
        return false;
    if (dot(cross2, faceNormal) < 0.0f)
        return false;

    const float area0 = glm::length(cross0) * 0.5f;
    const float area1 = glm::length(cross1) * 0.5f;
    const float area2 = glm::length(cross2) * 0.5f;

    const float areaSum = area0 + area1 + area2;

    w0 = area0 / areaSum;
    w1 = area1 / areaSum;

    return true;
}