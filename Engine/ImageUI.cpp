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

		rotationCenter.x = width / 2.f;
		rotationCenter.y = height / 2.f;

		scalingCenter.x = width / 2.f;
		scalingCenter.y = height / 2.f;

		rect.left = 0;
		rect.top = 0;
		rect.right = width;
		rect.bottom = height;
	}
}

ImageUI::~ImageUI() {

}

void ImageUI::Update(float dTime) {

}

void ImageUI::Render(ID2D1DeviceContext* d2dContext) {
	if (texture != nullptr) {
		d2dContext->SetTransform(D2D1::Matrix3x2F::Scale(scale.x, scale.y, scalingCenter)
			* D2D1::Matrix3x2F::Rotation(rotation, rotationCenter)
			* D2D1::Matrix3x2F::Translation(pos.x, pos.y));
		d2dContext->DrawBitmap(texture, &rect, color.a, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);
	}
}