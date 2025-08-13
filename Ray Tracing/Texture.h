#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

// Bilinear interpolation reference
// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/interpolation/bilinear-filtering


class Texture
{
public:
	int width, height, channels;
	std::vector<uint8_t> image;

	Texture(const std::string& filename);
	Texture(const int& width, const int& height, const std::vector<glm::vec3>& pixels);

	glm::vec3 GetWrapped(int i, int j);

	glm::vec3 InterpolateBilinear(
		const float& dx,
		const float& dy,
		const glm::vec3& c00,
		const glm::vec3& c10,
		const glm::vec3& c01,
		const glm::vec3& c11);

	glm::vec3 SamplePoint(const glm::vec2& uv); // Nearest sampling


	glm::vec3 SampleLinear(const glm::vec2& uv);
};