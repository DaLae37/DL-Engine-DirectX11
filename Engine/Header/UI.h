#pragma once
#include "pch.h"

class UI {
protected :
	D2D_MATRIX_3X2_F mat;
	D2D_RECT_F rect;

	D2D_POINT_2F scalingCenter;
	D2D_POINT_2F scale;

	D2D_POINT_2F rotationCenter;
	float rotation;

	D2D_POINT_2F position;
public :
	explicit UI();
	virtual ~UI();

	virtual void Update(float dTime) = 0;
	virtual void Render(ID2D1DeviceContext* d2dContext) = 0;

	void SetScale(D2D_POINT_2F newScale);
	void SetScalingCenter(D2D_POINT_2F newScalingCenter);
	void Scaling(D2D_POINT_2F scaleOffset);

	void SetRotation(float newRotation);
	void SetRotationCenter(D2D_POINT_2F newRotationCenter);
	void Rotate(float rotationOffset);

	void SetPosition(D2D_POINT_2F newPosition);
	void Translate(D2D_POINT_2F positionOffset);
};