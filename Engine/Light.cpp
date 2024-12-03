#include "pch.h"
#include "Light.h"

Light::Light() {

}

Light::~Light() {

}

WRL::ComPtr<ID3D11Buffer> Light::getConstantBuffer() {
	return this->constantBuffer;
}