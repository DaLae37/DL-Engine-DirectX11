#pragma once
#include "pch.h"
#include "UI.h"
#include "TextureManager.h"

class ImageUI : public UI
{
private :
	WRL::ComPtr<ID2D1Bitmap> texture;
	D2D_COLOR_F color;
	int width;
	int height;

	const wchar_t* path;
public :
	ImageUI(const wchar_t* path);
	~ImageUI();

	void Update(float deltaTime);
	void Render(ID2D1DeviceContext* d2dContext);
};