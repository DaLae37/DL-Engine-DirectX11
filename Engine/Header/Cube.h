#pragma once
#include "Object.h"

class Cube : public Object
{
private :
	const int NUM_VERTEX = 8;
	const int NUM_INDEX = 36;
public :
	Cube();
	~Cube();

	void Update(float deltaTime);
	void Render(ID3D11DeviceContext* d3dContext, Camera* camera);

	HRESULT CreatePipeline(ID3D11Device* d3dDevice);
	HRESULT CreateData(ID3D11Device* d3dDevice);
};