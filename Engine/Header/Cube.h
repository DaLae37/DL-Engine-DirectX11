#pragma once
#include "Object.h"

class Cube : public Object
{
private :

public :
	Cube();
	~Cube();

	void Update(float deltaTime);
	void Render(ID3D11DeviceContext* d3dContext, Camera* camera, Light* light);

	HRESULT CreatePipeline(ID3D11Device* d3dDevice);
	HRESULT CreateData(ID3D11Device* d3dDevice);
};