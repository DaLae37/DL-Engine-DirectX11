#include "pch.h"
#include "UI.h"

UI::UI() {
	mat = D2D_MATRIX_3X2_F{ 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };

	rect.top = 0;
	rect.left = 0;
	rect.right = 0;
	rect.bottom = 0;

	scalingCenter = D2D_POINT_2F{ 0, 0 };
	scale = D2D_POINT_2F{ 1.0f, 1.0f };
	
	rotationCenter = D2D_POINT_2F{ 0, 0 };
	rotation = 0;

	position = D2D_POINT_2F{ 0, 0 };
}

UI::~UI() {

}

void UI::SetPosition(D2D_POINT_2F newPosition) {
	this->position = newPosition;
}