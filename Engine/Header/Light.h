#pragma once
#include "pch.h"

struct LightBuffer {
	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 specular;

	DirectX::XMFLOAT4 direction;
};

class Light {

};