#pragma once

#include "Sphere.h"
#include "Ray.h"
#include "Light.h"
#include "Triangle.h"
#include "Square.h"

//#include "Hit.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

//namespace hlab
//{
	// 일반적으로는 헤더파일에서 using namespace std를 사용하지 않습니다.
	// 여기서는 강의 동영상에 녹화되는 코드 길이를 줄이기 위해서 사용하였습니다.
	// 예: std::vector -> vector
	//using namespace std;
	//using namespace glm;

	class Raytracer
	{
	public:
		int width, height;
		Light light;
		std::vector<std::shared_ptr<Object>> objects;

		Raytracer(const int& width, const int& height);

		Hit FindClosestCollision(Ray& ray);

		// 광선이 물체에 닿으면 그 물체의 색 반환
		glm::vec3 traceRay(Ray& ray, const int recurseLevel);

		void Render(std::vector<glm::vec4>& pixels);

		glm::vec3 TransformScreenToWorld(glm::vec2 posScreen);
	};
//}