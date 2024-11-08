#pragma once
#include "pch.h"

#define InputManagerInstance InputManager::getInstance()

class InputManager
{
private :
	InputManager();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	bool isInit = false;
	std::vector<bool> beforeKey;
	std::vector<bool> currentKey;

	HWND *hWnd;
public :
	~InputManager();

	static InputManager* getInstance();

	void Init(HWND* hWnd);
	void UpdateKeyState();
	int GetKeyState(int vk);
	std::pair<int, int> GetMousePos();
};