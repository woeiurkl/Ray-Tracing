#include "Raytracer.h"

#include "Sphere.h"
#include "Ray.h"
#include "Light.h"
#include "Triangle.h"
#include "Square.h"

Raytracer::Raytracer(const int& width, const int& height)
	: width(width), height(height)
{
	// Red Ball
	auto sphere1 = std::make_shared<Sphere>(glm::vec3(0.0f, -0.1f, 1.5f), 1.0f); // y = -0.1f z = 1.5f
	sphere1->amb = glm::vec3(0.1f);
	sphere1->dif = glm::vec3(1.0f, 0.0f, 0.0f);
	sphere1->spec = glm::vec3(1.0f);
	sphere1->alpha = 10.0f;
	sphere1->reflection = 0.0f;
	sphere1->transparency = 0.0f;
	objects.push_back(sphere1);

	// Metal Ball
	auto sphere2 = std::make_shared<Sphere>(glm::vec3(2.5f, 0.0f, 1.5f), 1.0f);
	sphere2->amb = glm::vec3(0.19f);
	sphere2->dif = glm::vec3(0.51f, 0.51f, 0.51f);
	sphere2->spec = glm::vec3(0.97f);
	sphere2->alpha = 300.0f;
	sphere2->reflection = 0.8f;
	sphere2->transparency = 0.0f;
	objects.push_back(sphere2);

	// Glass Ball
	auto sphere3 = std::make_shared<Sphere>(glm::vec3(-2.5f, 0.0f, 1.5f), 1.0f);
	sphere3->amb = glm::vec3(0.2f);
	sphere3->dif = glm::vec3(0.0f, 0.0f, 1.0f);
	sphere3->spec = glm::vec3(0.0f);
	sphere3->alpha = 50.0f;
	sphere3->reflection = 0.0f;
	sphere3->transparency = 1.0f;
	objects.push_back(sphere3);

	// Ground
	auto groundTexture = std::make_shared<Texture>("shadertoy_abstract1.jpg");
	auto ground = std::make_shared<Square>(glm::vec3(-10.0f, -1.2f, 0.0f), glm::vec3(-10.0f, -1.2f, 10.0f), glm::vec3(10.0f, -1.2f, 10.0f), glm::vec3(10.0f, -1.2f, 0.0f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	ground->amb = glm::vec4(1.0f);
	ground->dif = glm::vec4(1.0f);
	ground->spec = glm::vec4(1.0f);
	ground->alpha = 10.0f;
	ground->reflection = 0.0f;
	ground->ambTexture = groundTexture;
	ground->difTexture = groundTexture;

	objects.push_back(ground);

	light = Light{ {0.0f, 5.0f, -3.0f} }; // 화면 뒷쪽  {0.0f, 0.5f, -0.5f}
}

Hit Raytracer::FindClosestCollision(Ray& ray)
{
	float closestD = 1000.0; // inf
	Hit closestHit = Hit{ -1.0, glm::dvec3(0.0), glm::dvec3(0.0) };

	for (int l = 0; l < objects.size(); l++)
	{
		auto hit = objects[l]->CheckRayCollision(ray);

		if (hit.d >= 0.0f)
		{
			if (hit.d < closestD)
			{
				closestD = hit.d;
				closestHit = hit;
				closestHit.obj = objects[l];

				// 텍스춰 좌표
				closestHit.uv = hit.uv;
			}
		}
	}

	return closestHit;
}

glm::vec3 Raytracer::traceRay(Ray& ray, const int recurseLevel)
{
	if (recurseLevel < 0)
		return glm::vec3(0.0f);

	// Render first hit
	const auto hit = FindClosestCollision(ray);

	if (hit.d >= 0.0f)
	{
		glm::vec3 color(0.0f);  // 0.0f

		const glm::vec3 dirToLight = glm::normalize(light.pos - hit.point);

		// 그림자
		Ray shadowRay = { hit.point + dirToLight * 0.01f, dirToLight };
		if (FindClosestCollision(shadowRay).d < 0.0f)
		{
			glm::vec3 phongColor(0.0f);

			const float diff = glm::max(dot(hit.normal, dirToLight), 0.0f);
			const glm::vec3 reflectDir = 2.0f * hit.normal * dot(dirToLight, hit.normal) - dirToLight;
			const float specular = glm::pow(glm::max(glm::dot(-ray.dir, reflectDir), 0.0f), hit.obj->alpha);

			if (hit.obj->ambTexture)
			{
				phongColor += hit.obj->amb * hit.obj->ambTexture->SampleLinear(hit.uv);
			}
			else
			{
				 phongColor += hit.obj->amb;
			}

			if (hit.obj->difTexture)
			{
				phongColor += diff * hit.obj->dif * hit.obj->difTexture->SampleLinear(hit.uv);
			}
			else
			{
				phongColor += diff * hit.obj->dif;
			}

			phongColor += hit.obj->spec * specular;

			color += phongColor * (1.0f - hit.obj->reflection - hit.obj->transparency);

			if (hit.obj->reflection)
			{
				// 여기에 반사 구현
				// 수치 오류 주의
				// 반사광이 반환해준 색을 더할 때의 비율은 hit.obj->reflection

				const glm::vec3 m = ray.dir + hit.normal * glm::dot(hit.normal, -ray.dir);
				const glm::vec3 reflectedDirection = glm::normalize(2.0f * m - ray.dir);
				Ray reflection_ray{ hit.point + 1e-4f * reflectedDirection, reflectedDirection };
				color += traceRay(reflection_ray, recurseLevel - 1) * hit.obj->reflection;
			}

			if (hit.obj->transparency)
			{
				// 투명한 물체의 굴절 처리
				const float ior = 1.5f; // Index of refraction (유리: 1.5, 물: 1.3)

				float eta; // sinTheta1 / sinTheta2
				glm::vec3 normal;

				if (glm::dot(ray.dir, hit.normal) < 0.0f) // 밖에서 안에서 들어가는 경우 (예: 공기->유리)
				{
					eta = ior;
					normal = hit.normal;
				}
				else // 안에서 밖으로 나가는 경우 (예: 유리->공기)
				{
					eta = 1.0f / ior;
					normal = -hit.normal;
				}

				const float costheta1 = glm::dot(normal, -ray.dir);
				const float sintheta1 = glm::sqrt(1.0f - costheta1 * costheta1); // cos^2 + sin^2 = 1
				const float sintheta2 = sintheta1 / eta;
				const float costheta2 = glm::sqrt(1.0f - sintheta2 * sintheta2);

				const glm::vec3 m = glm::normalize(dot(normal, -ray.dir) * normal + ray.dir);
				const glm::vec3 a = m * sintheta2;
				const glm::vec3 b = -normal * costheta2;
				const glm::vec3 refracteddirection = glm::normalize(a + b); // transmission

				Ray refractedRay{ hit.point + refracteddirection * 0.0001f, refracteddirection };

				color += traceRay(refractedRay, recurseLevel - 1) * hit.obj->transparency;
			}
		}
		else
		{
			if (hit.obj->ambTexture)
			{
				color += hit.obj->amb * hit.obj->ambTexture->SampleLinear(hit.uv);
			}
			else
			{
				color += hit.obj->amb;
			}

			if (hit.obj->reflection)
			{
				// 여기에 반사 구현
				// 수치 오류 주의
				// 반사광이 반환해준 색을 더할 때의 비율은 hit.obj->reflection

				const glm::vec3 m = ray.dir + hit.normal * glm::dot(hit.normal, -ray.dir);
				const glm::vec3 reflectedDirection = glm::normalize(2.0f * m - ray.dir);
				Ray reflection_ray{ hit.point + 1e-4f * reflectedDirection, reflectedDirection };
				color += traceRay(reflection_ray, recurseLevel - 1) * hit.obj->reflection;
			}

			if (hit.obj->transparency)
			{
				// 투명한 물체의 굴절 처리
				const float ior = 1.5f; // Index of refraction (유리: 1.5, 물: 1.3)

				float eta; // sinTheta1 / sinTheta2
				glm::vec3 normal;

				if (glm::dot(ray.dir, hit.normal) < 0.0f) // 밖에서 안에서 들어가는 경우 (예: 공기->유리)
				{
					eta = ior;
					normal = hit.normal;
				}
				else // 안에서 밖으로 나가는 경우 (예: 유리->공기)
				{
					eta = 1.0f / ior;
					normal = -hit.normal;
				}

				const float costheta1 = glm::dot(normal, -ray.dir);
				const float sintheta1 = glm::sqrt(1.0f - costheta1 * costheta1); // cos^2 + sin^2 = 1
				const float sintheta2 = sintheta1 / eta;
				const float costheta2 = glm::sqrt(1.0f - sintheta2 * sintheta2);

				const glm::vec3 m = glm::normalize(dot(normal, -ray.dir) * normal + ray.dir);
				const glm::vec3 a = m * sintheta2;
				const glm::vec3 b = -normal * costheta2;
				const glm::vec3 refracteddirection = glm::normalize(a + b); // transmission

				Ray refractedRay{ hit.point + refracteddirection * 0.0001f, refracteddirection };

				color += traceRay(refractedRay, recurseLevel - 1) * hit.obj->transparency;
			}
		}

		return color;
	}

	return glm::vec3(0.0f);
}

void Raytracer::Render(std::vector<glm::vec4>& pixels)
{
	std::fill(pixels.begin(), pixels.end(), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	const glm::vec3 eyePos(0.0f, 0.0f, -1.5f);

#pragma omp parallel for
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			const glm::vec3 pixelPosWorld = TransformScreenToWorld(glm::vec2(i, j));
			Ray pixelRay{ pixelPosWorld, glm::normalize(pixelPosWorld - eyePos) };
			pixels[i + width * j] = glm::vec4(glm::clamp(traceRay(pixelRay, 5), 0.0f, 1.0f), 1.0f);
		}
}

glm::vec3 Raytracer::TransformScreenToWorld(glm::vec2 posScreen)
{
	const float xScale = 2.0f / this->width;
	const float yScale = 2.0f / this->height;
	const float aspect = float(this->width) / this->height;

	// 3차원 공간으로 확장 (z좌표는 0.0)
	return glm::vec3((posScreen.x * xScale - 1.0f) * aspect, -posScreen.y * yScale + 1.0f, 0.0f);
}