#pragma once
#include "pch.h"

#define InputManagerInstance InputManager::getInstance()

class InputManager
{
private :
	const int NUM_KEY = 256;

	InputManager();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	bool isInit = false;
	std::vector<bool> beforeKey = std::vector<bool>(NUM_KEY, false);
	std::vector<bool> currentKey = std::vector<bool>(NUM_KEY, false);

	HWND *hWnd;
public :
	~InputManager();

	static InputManager* getInstance();

	void Init(HWND* hWnd);
	void UpdateKeyState();
	int GetKeyState(int vk);
	POINT GetMousePos();
};