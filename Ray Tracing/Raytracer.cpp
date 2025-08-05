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
	auto sphere1 = std::make_shared<Sphere>(glm::vec3(0.0f, 0.15f, 1.5f), 0.65f); //
	sphere1->amb = glm::vec3(0.1f);
	sphere1->dif = glm::vec3(1.0f, 0.0f, 0.0f);
	sphere1->spec = glm::vec3(1.0f);
	sphere1->alpha = 10.0f;
	sphere1->reflection = 0.05f;
	sphere1->transparency = 0.0f;
	objects.push_back(sphere1);

	// Metal Ball
	auto sphere2 = std::make_shared<Sphere>(glm::vec3(-2.2f, 0.15f, 1.5f), 0.65f);  // 2.6f, -0.1f, 3.0f
	sphere2->amb = glm::vec3(0.19f);
	sphere2->dif = glm::vec3(0.75f, 0.75f, 0.75f);
	sphere2->spec = glm::vec3(0.77f);
	sphere2->alpha = 300.0f;
	sphere2->reflection = 0.6f;
	sphere2->transparency = 0.0f;
	objects.push_back(sphere2);

	// Glass Ball
	auto sphere3 = std::make_shared<Sphere>(glm::vec3(2.2f, 0.15f, 1.5f), 0.65f);  // -2.5f, 0.35f, 2.0f
	sphere3->amb = glm::vec3(0.1f);
	sphere3->dif = glm::vec3(0.0f);
	sphere3->spec = glm::vec3(0.9f);
	sphere3->alpha = 500.0f;
	sphere3->reflection = 0.1f;
	sphere3->transparency = 0.9f;
	objects.push_back(sphere3);



	// water
	auto water = std::make_shared<Square>(glm::vec3(-10.0f, -0.5f, 8.4f), glm::vec3(10.0f, -0.5f, 8.4f), glm::vec3(10.0f, -0.5f, -1.6f), glm::vec3(-10.0f, -0.5f, -1.6f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	water->amb = glm::vec3(0.0f, 0.003f, 0.006f);
	water->dif = glm::vec3(0.05f, 0.1f, 0.15f);
	water->spec = glm::vec3(1.0f, 1.0f, 1.0f);
	water->alpha = 1000.0f;
	water->reflection = 1.0f;
	water->transparency = 1.0f;
	water->fresnel = true;
	water->ior = 1.33f;
	objects.push_back(water);

	// right cube
	auto pxTexture = std::make_shared<Texture>("px.jpg");
	auto px = std::make_shared<Square>(glm::vec3(10.0f, 7.75f, 8.4f), glm::vec3(10.0f, 7.75f, -1.6f), glm::vec3(10.0f, -2.25f, -1.6f), glm::vec3(10.0f, -2.25f, 8.4f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	px->amb = glm::vec3(1.0f);
	px->dif = glm::vec3(1.0f);
	px->spec = glm::vec3(1.0f);
	px->alpha = 10.0f;
	px->reflection = 0.0f;
	px->ambTexture = pxTexture;
	px->difTexture = pxTexture;
	objects.push_back(px);

	// left cube
	auto nxTexture = std::make_shared<Texture>("nx.jpg");
	auto nx = std::make_shared<Square>(glm::vec3(-10.0f, 7.75f, -1.6f), glm::vec3(-10.0f, 7.75f, 8.4f), glm::vec3(-10.0f, -2.25f, 8.4f), glm::vec3(-10.0f, -2.25f, -1.6f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	nx->amb = glm::vec3(1.0f);
	nx->dif = glm::vec3(1.0f);
	nx->spec = glm::vec3(1.0f);
	nx->alpha = 10.0f;
	nx->reflection = 0.0f;
	nx->ambTexture = nxTexture;
	nx->difTexture = nxTexture;
	objects.push_back(nx);

	// up cube
	auto pyTexture = std::make_shared<Texture>("py.jpg");
	auto py = std::make_shared<Square>(glm::vec3(-10.0f, 7.75f, -1.6f), glm::vec3(10.0f, 7.75f, -1.6f), glm::vec3(10.0f, 7.75f, 8.4f), glm::vec3(-10.0f, 7.75f, 8.4f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	py->amb = glm::vec3(1.0f);
	py->dif = glm::vec3(1.0f);
	py->spec = glm::vec3(1.0f);
	py->alpha = 10.0f;
	py->reflection = 0.0f;
	py->ambTexture = pyTexture;
	py->difTexture = pyTexture;
	objects.push_back(py);

	// down cube   
	auto nyTexture = std::make_shared<Texture>("ny.jpg");
	auto ny = std::make_shared<Square>(glm::vec3(-10.0f, -2.0f, 8.4f), glm::vec3(10.0f, -2.0f, 8.4f), glm::vec3(10.0f, -2.0f, -1.6f), glm::vec3(-10.0f, -2.0f, -1.6f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	ny->amb = glm::vec3(1.0f);
	ny->dif = glm::vec3(1.0f);
	ny->spec = glm::vec3(1.0f);
	ny->alpha = 10.0f;
	ny->reflection = 0.0f;
	ny->ambTexture = nyTexture;
	ny->difTexture = nyTexture;
	objects.push_back(ny);

	// front cube
	auto pzTexture = std::make_shared<Texture>("pz.jpg");
	auto pz = std::make_shared<Square>(glm::vec3(-10.0f, 7.75f, 8.4f), glm::vec3(10.0f, 7.75f, 8.4f), glm::vec3(10.0f, -2.25f, 8.4f), glm::vec3(-10.0f, -2.25f, 8.4f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	pz->amb = glm::vec3(1.0f);
	pz->dif = glm::vec3(1.0f);
	pz->spec = glm::vec3(1.0f);
	pz->alpha = 10.0f;
	pz->reflection = 0.0f;
	pz->ambTexture = pzTexture;
	pz->difTexture = pzTexture;
	objects.push_back(pz);

	// back cube
	auto nzTexture = std::make_shared<Texture>("nz.jpg");
	auto nz = std::make_shared<Square>(glm::vec3(10.0f, 7.75f, -1.6f), glm::vec3(-10.0f, 7.75f, -1.6f), glm::vec3(-10.0f, -2.25f, -1.6f), glm::vec3(10.0f, -2.25f, -1.6f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	nz->amb = glm::vec3(1.0f);
	nz->dif = glm::vec3(1.0f);
	nz->spec = glm::vec3(1.0f);
	nz->alpha = 10.0f;
	nz->reflection = 0.0f;
	nz->ambTexture = nzTexture;
	nz->difTexture = nzTexture;
	objects.push_back(nz);



	light = Light{ {-0.5f, 0.6f, 0.1f}, 0.6f }; // 화면 뒷쪽  {0.0f, 0.5f, -0.5f}   eyePos(0.0f, 0.0f, -1.5f);
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
		auto shadowHit = FindClosestCollision(shadowRay);
		float distToLight = glm::length(light.pos - hit.point);
		bool inShadow = (shadowHit.d >= 0.0f && shadowHit.d < distToLight);

		if (!inShadow)  // no shadow
		{
			glm::vec3 phongColor(0.0f);

			const float diff = glm::max(dot(hit.normal, dirToLight), 0.0f);
			const glm::vec3 reflectDir = 2.0f * hit.normal * dot(dirToLight, hit.normal) - dirToLight;
			const float specular = glm::pow(glm::max(glm::dot(-ray.dir, reflectDir), 0.0f), hit.obj->alpha);

			if (hit.obj->ambTexture)
			{
				phongColor += hit.obj->amb * hit.obj->ambTexture->SampleLinear(hit.uv) * light.intensity;
			}
			else
			{
				 phongColor += hit.obj->amb;
			}

			if (hit.obj->difTexture)
			{
				phongColor += diff * hit.obj->dif * hit.obj->difTexture->SampleLinear(hit.uv) * light.intensity;
			}
			else
			{
				phongColor += diff * hit.obj->dif * light.intensity * 1.3f;
			}

			phongColor += hit.obj->spec * specular * light.intensity; // multiply light.intensity cause the cube map was too bright

			color += phongColor * (1.0f - hit.obj->reflection - hit.obj->transparency);

			if (hit.obj->fresnel) // for water
			{
				float kr = calculateFresnel(ray.dir, hit.normal, hit.obj->ior);

				// reflection
				const glm::vec3 refrlectionM = ray.dir + hit.normal * glm::dot(hit.normal, -ray.dir);
				const glm::vec3 reflectedDirection = glm::normalize(2.0f * refrlectionM - ray.dir);
				Ray reflection_ray{ hit.point + 1e-4f * reflectedDirection, reflectedDirection };
				auto reflectionColor = traceRay(reflection_ray, recurseLevel - 1) * hit.obj->reflection;

				// refraction
				float eta; // sinTheta1 / sinTheta2
				glm::vec3 normal;

				if (glm::dot(ray.dir, hit.normal) < 0.0f) // 밖에서 안에서 들어가는 경우 (예: 공기->유리)
				{
					eta = hit.obj->ior;
					normal = hit.normal;
				}
				else // 안에서 밖으로 나가는 경우 (예: 유리->공기)
				{
					eta = 1.0f / hit.obj->ior;
					normal = -hit.normal;
				}

				const float costheta1 = glm::dot(normal, -ray.dir);
				const float sintheta1 = glm::sqrt(1.0f - costheta1 * costheta1); // cos^2 + sin^2 = 1
				const float sintheta2 = sintheta1 / eta;
				const float costheta2 = glm::sqrt(1.0f - sintheta2 * sintheta2);

				const glm::vec3 refractionM = glm::normalize(dot(normal, -ray.dir) * normal + ray.dir);
				const glm::vec3 a = refractionM * sintheta2;
				const glm::vec3 b = -normal * costheta2;
				const glm::vec3 refracteddirection = glm::normalize(a + b); // transmission

				Ray refractedRay{ hit.point + refracteddirection * 0.0001f, refracteddirection };

				glm::vec3 refractionColor = traceRay(refractedRay, recurseLevel - 1) * hit.obj->transparency;



				color += reflectionColor * kr + refractionColor * (1 - kr);
			}
			else  // no fresnel
			{
				//color += phongColor * (1.0f - hit.obj->reflection - hit.obj->transparency);

				if (hit.obj->reflection)
				{
					// 여기에 반사 구현
					// 수치 오류 주의
					// 반사광이 반환해준 색을 더할 때의 비율은 hit.obj->reflection

					const glm::vec3 reflectionM = ray.dir + hit.normal * glm::dot(hit.normal, -ray.dir);
					const glm::vec3 reflectedDirection = glm::normalize(2.0f * reflectionM - ray.dir);
					Ray reflection_ray{ hit.point + 1e-4f * reflectedDirection, reflectedDirection };
					color += traceRay(reflection_ray, recurseLevel - 1) * hit.obj->reflection;
				}

				if (hit.obj->transparency) // for balls
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

					const glm::vec3 refractionM = glm::normalize(dot(normal, -ray.dir) * normal + ray.dir);
					const glm::vec3 a = refractionM * sintheta2;
					const glm::vec3 b = -normal * costheta2;
					const glm::vec3 refracteddirection = glm::normalize(a + b); // transmission

					Ray refractedRay{ hit.point + refracteddirection * 0.0001f, refracteddirection };

					color += traceRay(refractedRay, recurseLevel - 1) * hit.obj->transparency;
				}
			}
		}
		else  // shadow
		{
			if (hit.obj->ambTexture)
			{
				color += hit.obj->amb * hit.obj->ambTexture->SampleLinear(hit.uv) / 1.5f;  // /1.5f because map's amb is 1.0f
			}
			else
			{
				color += hit.obj->amb;
			}

			if (hit.obj->fresnel)  // fresnel
			{
				float kr = calculateFresnel(ray.dir, hit.normal, hit.obj->ior);

				// reflection
				const glm::vec3 reflectionM = ray.dir + hit.normal * glm::dot(hit.normal, -ray.dir);
				const glm::vec3 reflectedDirection = glm::normalize(2.0f * reflectionM - ray.dir);
				Ray reflection_ray{ hit.point + 1e-4f * reflectedDirection, reflectedDirection };
				auto reflectionColor = traceRay(reflection_ray, recurseLevel - 1) * hit.obj->reflection;

				// refraction
				float eta; // sinTheta1 / sinTheta2
				glm::vec3 normal;

				if (glm::dot(ray.dir, hit.normal) < 0.0f) // 밖에서 안에서 들어가는 경우 (예: 공기->유리)
				{
					eta = hit.obj->ior;
					normal = hit.normal;
				}
				else // 안에서 밖으로 나가는 경우 (예: 유리->공기)
				{
					eta = 1.0f / hit.obj->ior;
					normal = -hit.normal;
				}

				const float costheta1 = glm::dot(normal, -ray.dir);
				const float sintheta1 = glm::sqrt(1.0f - costheta1 * costheta1); // cos^2 + sin^2 = 1
				const float sintheta2 = sintheta1 / eta;
				const float costheta2 = glm::sqrt(1.0f - sintheta2 * sintheta2);

				const glm::vec3 refractionM = glm::normalize(dot(normal, -ray.dir) * normal + ray.dir);
				const glm::vec3 a = refractionM * sintheta2;
				const glm::vec3 b = -normal * costheta2;
				const glm::vec3 refracteddirection = glm::normalize(a + b); // transmission

				Ray refractedRay{ hit.point + refracteddirection * 0.0001f, refracteddirection };

				auto refractionColor = traceRay(refractedRay, recurseLevel - 1) * hit.obj->transparency;


				color += reflectionColor * kr + refractionColor * (1 - kr);
			}
			else  // no fresnel
			{
				if (hit.obj->reflection)
				{
					const glm::vec3 m = ray.dir + hit.normal * glm::dot(hit.normal, -ray.dir);
					const glm::vec3 reflectedDirection = glm::normalize(2.0f * m - ray.dir);
					Ray reflection_ray{ hit.point + 1e-4f * reflectedDirection, reflectedDirection };
					color += traceRay(reflection_ray, recurseLevel - 1) * hit.obj->reflection;
				}

				if (hit.obj->transparency)
				{
					const float ior = 1.5f;
					float eta;
					glm::vec3 normal;

					if (glm::dot(ray.dir, hit.normal) < 0.0f)
					{
						eta = ior;
						normal = hit.normal;
					}
					else
					{
						eta = 1.0f / ior;
						normal = -hit.normal;
					}

					const float costheta1 = glm::dot(normal, -ray.dir);
					const float sintheta1 = glm::sqrt(1.0f - costheta1 * costheta1);
					const float sintheta2 = sintheta1 / eta;
					const float costheta2 = glm::sqrt(1.0f - sintheta2 * sintheta2);

					const glm::vec3 m = glm::normalize(dot(normal, -ray.dir) * normal + ray.dir);
					const glm::vec3 a = m * sintheta2;
					const glm::vec3 b = -normal * costheta2;
					const glm::vec3 refracteddirection = glm::normalize(a + b);

					Ray refractedRay{ hit.point + refracteddirection * 0.0001f, refracteddirection };
					color += traceRay(refractedRay, recurseLevel - 1) * hit.obj->transparency;
				}
			}
		}

		return color;
	}

	return glm::vec3(0.0f);
}

void Raytracer::Render(std::vector<glm::vec4>& pixels)
{
	std::fill(pixels.begin(), pixels.end(), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	const glm::vec3 eyePos(0.0f, 0.0f, -1.5f); // eyePos(0.0f, 0.0f, -1.5f);

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

float Raytracer::calculateFresnel(const glm::vec3& incident, const glm::vec3& normal, float ior)
{
	float cosi = glm::clamp(glm::dot(incident, normal), -1.0f, 1.0f);
	float etai = 1.0f;
	float etat = ior;

	if (cosi > 0)
	{
		std::swap(etai, etat);
	}

	float sint = etai / etat * glm::sqrt(glm::max(0.0f, 1.0f - cosi * cosi));

	if (sint >= 1.0f)
	{
		return 1.0f;
	}
	else
	{
		float cost = glm::sqrt(glm::max(0.0f, 1.0f - sint * sint));
		cosi = glm::abs(cosi);

		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));

		float kr = (Rs * Rs + Rp * Rp) / 2.0f;

		return kr;
	}
}