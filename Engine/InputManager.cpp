#include "pch.h"
#include "InputManager.h"

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

InputManager* InputManager::getInstance() {
	static InputManager instance;
	return &instance;
}

void InputManager::Init(HWND* hWnd) {
	this->hWnd = hWnd;

	this->isInit = true;
}

void InputManager::UpdateKeyState() {
	for (int i = 0; i < 256; i++) {
		beforeKey[i] = currentKey[i];
		currentKey[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

int InputManager::GetKeyState(int vk) {
	if (beforeKey[vk] && currentKey[vk]) {
		return KEY_ON;
	}
	else if (!beforeKey[vk] && currentKey[vk]) {
		return KEY_DOWN;
	}
	else if (beforeKey[vk] && !currentKey[vk]) {
		return KEY_UP;
	}
	else {
		return KEY_NONE;
	}
}

std::pair<int, int> InputManager::GetMousePos() {
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(*hWnd, &p);

	return { p.x, p.y };
}