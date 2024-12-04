#pragma once
#include "pch.h"

#define ShaderManagerInstance ShaderManager::getInstance()

class ShaderManager
{
private :
	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
	
public :
	~ShaderManager();

	static ShaderManager* getInstance();

	void Init();
};