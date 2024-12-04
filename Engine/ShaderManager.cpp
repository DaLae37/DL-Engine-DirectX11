#include "pch.h"
#include "ShaderManager.h"

ShaderManager::~ShaderManager() {

}

ShaderManager* ShaderManager::getInstance() {
	static ShaderManager instance;
	return &instance;
}

void ShaderManager::Init() {

}