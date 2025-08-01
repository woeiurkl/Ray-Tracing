﻿#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"

Texture::Texture(const std::string& filename)
{
	unsigned char* img = stbi_load(filename.c_str(), &width, &height, &channels, 0);

	image.resize(width * height * channels);
	memcpy(image.data(), img, image.size() * sizeof(uint8_t));

	delete img;
}

Texture::Texture(const int& width, const int& height, const std::vector<glm::vec3>& pixels)
	: width(width), height(height), channels(3)
{
	image.resize(width * height * channels);

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			const auto& color = pixels[i + j * width];

			image[(i + width * j) * channels + 0] = uint8_t(color.r * 255);
			image[(i + width * j) * channels + 1] = uint8_t(color.g * 255);
			image[(i + width * j) * channels + 2] = uint8_t(color.b * 255);
		}
}

glm::vec3 Texture::GetWrapped(int i, int j)
{
	i %= width; // i가 width면 0으로 바뀜
	j %= height;

	if (i < 0)
		i += width; // i가 -1이면 (width-1)로 바뀜
	if (j < 0)
		j += height;

	const float r = image[(i + width * j) * channels + 0] / 255.0f;
	const float g = image[(i + width * j) * channels + 1] / 255.0f;
	const float b = image[(i + width * j) * channels + 2] / 255.0f;

	return glm::vec3(r, g, b);
}

glm::vec3 Texture::InterpolateBilinear(
	const float& dx,
	const float& dy,
	const glm::vec3& c00,
	const glm::vec3& c10,
	const glm::vec3& c01,
	const glm::vec3& c11)
{
	glm::vec3 a = c00 * (1.0f - dx) + c10 * dx;
	glm::vec3 b = c01 * (1.0f - dx) + c11 * dx;
	return a * (1.0f - dy) + b * dy;
}

glm::vec3 Texture::SamplePoint(const glm::vec2& uv) // Nearest sampling이라고 부르기도 함
{
	// 텍스춰 좌표의 범위 uv [0.0, 1.0] x [0.0, 1.0]
	// 이미지 좌표의 범위 xy [-0.5, width - 1 + 0.5] x [-0.5, height - 1 + 0.5]
	glm::vec2 xy = uv * glm::vec2(width, height) - glm::vec2(0.5f);
	xy += glm::vec2(0.5f);

	int i = int(xy.x);
	int j = int(xy.y);

	return GetWrapped(i, j);
}

glm::vec3 Texture::SampleLinear(const glm::vec2& uv)
{
	// 텍스춰 좌표의 범위 uv [0.0, 1.0] x [0.0, 1.0]
	// 이미지 좌표의 범위 xy [-0.5, width - 1 + 0.5] x [-0.5, height - 1 + 0.5]
	// std::cout << floor(-0.3f) << " " << int(-0.3f) << std::endl; // -1 0

	const glm::vec2 xy = uv * glm::vec2(width, height) - glm::vec2(0.5f);
	const int i = int(floor(xy.x));
	const int j = int(floor(xy.y));
	const float dx = xy.x - float(i);
	const float dy = xy.y - float(j);

	return InterpolateBilinear(dx, dy, GetWrapped(i, j), GetWrapped(i + 1, j), GetWrapped(i, j + 1), GetWrapped(i + 1, j + 1));
}