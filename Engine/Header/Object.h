#pragma once
#include "pch.h"

class Object {
private :

public :
	Object();
	virtual ~Object();

	virtual void Update(float dTime) = 0;
	virtual void Render() = 0;
};