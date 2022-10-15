#pragma once

#include <string>
#include <chrono>

#include "GlfwSetup.h"

#include "cWindow.h"

using time_point = std::chrono::system_clock::time_point;

struct KeyState
{
	bool bHeld;
	bool bPressed;
	bool bReleased;
};

class cThread
{
public:
	cThread();
	~cThread();

private:
	KeyState m_ksKeys[512];
	KeyState m_ksMouse[5];

	bool m_nKeyOldState[512];
	bool m_nKeyNewState[512];

	bool m_nMouseOldState[5];
	bool m_nMouseNewState[5];

	float m_fWheelDelta = 0.0f;

	int m_nMouseX = -1;
	int m_nMouseY = -1;

	float m_fDeltaTime;

	time_point m_tpStart = time_point(std::chrono::milliseconds(0));
	time_point m_tpEnd = time_point(std::chrono::milliseconds(0));

public:
	bool Run(cWindow& wnd);
	
	float GetDeltaTime() const;

	int GetMouseX() const;
	int GetMouseY() const;

	const vi2d& GetMouse() const;

	KeyState GetKey(short key) const;
	KeyState GetMouse(short key) const;

	void Refresh(cWindow& wnd);

};
