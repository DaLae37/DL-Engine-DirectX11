#include "pch.h"
#include "ImageUI.h"

ImageUI::ImageUI(const std::filesystem::path& path) {
	this->path = path;
	width = 0;
	height = 0;
	color = D2D_COLOR_F{ 1.0f, 1.0f, 1.0f, 1.0f };

	texture = TextureManagerInstance->LoadD2DTextureFromFile(path).Get();
	if (texture != nullptr) {
		D2D_SIZE_U textureSize = texture->GetPixelSize();
		width = textureSize.width;
		height = textureSize.height;

		rotationCenter.x = width / 2.0f;
		rotationCenter.y = height / 2.0f;

		scalingCenter.x = 0;
		scalingCenter.y = 0;

		rect.left = position.x;
		rect.top = position.y;
		rect.right = position.x + width;
		rect.bottom = position.y + height;
	}
}

ImageUI::~ImageUI() {

}

void ImageUI::Update(float dTime) {
	rect.left = position.x;
	rect.top = position.y;
	rect.right = position.x + width * scale.x;
	rect.bottom = position.y + height * scale.y;
}

void ImageUI::Render(ID2D1DeviceContext* d2dContext) {
	if (texture != nullptr) {
		d2dContext->SetTransform(D2D1::Matrix3x2F::Scale(scale.x, scale.y, scalingCenter)
			* D2D1::Matrix3x2F::Rotation(rotation, rotationCenter)
			* D2D1::Matrix3x2F::Translation(position.x, position.y));
		d2dContext->DrawBitmap(texture, &rect, color.a, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);
	}
}