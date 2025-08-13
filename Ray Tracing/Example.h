#pragma once

#include "Raytracer.h"

#include <windows.h>
#include <memory>
#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include <chrono>
#include <algorithm>

struct Vertex
{
	glm::vec4 pos;
	glm::vec2 uv;
};

class Example
{
public:
	int width, height;
	Raytracer raytracer;
	std::vector<glm::vec4> pixels;

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	D3D11_VIEWPORT viewport;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Texture2D* canvasTexture = nullptr;
	ID3D11ShaderResourceView* canvasTextureView = nullptr;
	ID3D11RenderTargetView* canvasRenderTargetView = nullptr;
	ID3D11SamplerState* colorSampler;
	UINT indexCount;

public:
	Example(HWND window, int width, int height);

	void Update();

	// https://docs.microsoft.com/en-us/windows/win32/direct3d11/how-to--compile-a-shader
	void InitShaders();

	void Initialize(HWND window, int width, int height);

	void Render();

	void Clean();
};