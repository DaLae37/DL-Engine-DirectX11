#pragma once
#include "pch.h"

// Singleton Pattern
#define InputManagerInstance InputManager::getInstance()

// Max Virtual Key
#define NUM_KEY 256
class InputManager {
private:
	// Singleton Pattern Safety
	InputManager() = default;
	// Remove Copy Constructor
	InputManager(const InputManager&) = delete;
	// Remove Substitution Operator
	InputManager& operator=(const InputManager&) = delete;

	std::vector<bool> beforeKey = std::vector<bool>(NUM_KEY, false);
	std::vector<bool> currentKey = std::vector<bool>(NUM_KEY, false);

	// When Instance is Initialized, Changed to true
	bool isInit = false;

	// Get Raw Pointer from Window
	HWND* hWnd = nullptr;

public:
	~InputManager();

	// Get InputManager's Instance
	static InputManager* getInstance();

	// Initialize InputManager Instance *Must Called Before Using Any Functions*
	void Init(HWND* hWnd);
	// Update Key State *Need to Call Every Frame*
	void UpdateKeyState();
	// Get Current Key State
	int GetKeyState(int vk);
	// Get Current Mouse Position
	POINT GetMousePosition();
};