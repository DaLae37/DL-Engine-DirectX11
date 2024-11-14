#pragma once
#include "UI.h"
#include "TextureManager.h"

class ImageUI : public UI
{
private :
	D2D_COLOR_F color;
	int width;
	int height;

	std::filesystem::path path;
	ID2D1Bitmap* texture;
public :
	ImageUI(const std::filesystem::path& path);
	~ImageUI();

	void Update(float deltaTime);
	void Render(ID2D1DeviceContext* d2dContext);
};