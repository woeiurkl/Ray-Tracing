#pragma once

#include "Sphere.h"
#include "Ray.h"
#include "Light.h"
#include "Triangle.h"
#include "Square.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

class Raytracer
{
public:
	int width, height;
	Light light;
	std::vector<std::shared_ptr<Object>> objects;

	// DoF
	float defocusAngle = 0.0f;
	float focusDist = 3.0f;
	glm::vec3 defocusDisk_u;
	glm::vec3 defocusDisk_v;
	glm::vec3 cameraCenter;
	glm::vec3 u, v, w;

	Raytracer(const int& width, const int& height);

	Hit FindClosestCollision(Ray& ray);

	glm::vec3 traceRay(Ray& ray, const int recurseLevel);

	void Render(std::vector<glm::vec4>& pixels);

	glm::vec3 TransformScreenToWorld(glm::vec2 posScreen);

	float calculateFresnel(const glm::vec3& incident, const glm::vec3& normal, float ior);

	// DoF
	void InitializeCamera();
	float RandomFloat() const;
	float RandomFloat(float min, float max) const;
	glm::vec3 RandomInUnitDisk() const;
	glm::vec3 DefocusDiskSample() const;
};