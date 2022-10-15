#pragma once

#include "GlfwSetup.h"
#include "Vec.h"

#include <string>

#define WINDOW_PREFIX std::string("Window: ")

class cWindow
{
public:
	cWindow(uint32_t screen_width, uint32_t screen_height, const std::string& app_name, bool vsync = false, bool full_screen = false, bool dirty_pixel = false, float znear = 1.0f, float zfar = 1000.0f);
	~cWindow();

private:
	GLFWwindow* m_glWindow;
	GLFWmonitor* m_glMonitor;

	bool m_bVSync;
	bool m_bFullScreen;

	bool m_bDirtyPixel;

	std::string m_sAppName;
	std::string m_sIconFilename;

	int m_nWidth;
	int m_nHeight;

	std::string m_sErrMsg;

	float m_fZNear;
	float m_fZFar;

public:
	bool Construct();

	const std::string& GetErrMessage() const;

	GLFWwindow* GetGLFWwindow() const;

	bool VSync() const;
	bool FullScreen() const;
	bool DirtyPixel() const;

	void SetIcon(uint8_t* data, int width, int height);

	int GetScreenWidth() const;
	int GetScreenHeight() const;

	const vi2d& GetScreenSize() const;

};

