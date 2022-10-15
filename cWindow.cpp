#include "cWindow.h"

cWindow::cWindow(uint32_t screen_width, uint32_t screen_height, const std::string& app_name, bool vsync, bool full_screen, bool dirty_pixel, float znear, float zfar)
{
	m_nWidth = screen_width;
	m_nHeight = screen_height;

	m_sAppName = app_name;

	m_bVSync = vsync;
	m_bFullScreen = full_screen;

	m_bDirtyPixel = dirty_pixel;

	m_fZNear = znear;
	m_fZFar = zfar;
}

cWindow::~cWindow()
{
	glfwDestroyWindow(m_glWindow);
}

bool cWindow::Construct()
{
	m_glMonitor = glfwGetPrimaryMonitor();

	if (!m_glMonitor)
	{
		m_sErrMsg = WINDOW_PREFIX + "can't get monitor info";
		return false;
	}

	const GLFWvidmode* vm = glfwGetVideoMode(m_glMonitor);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	if (m_bVSync)
	{
		glfwSwapInterval(1);
		glfwWindowHint(GLFW_REFRESH_RATE, vm->refreshRate);
	}
	else
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

	if (m_bFullScreen)
	{
		m_nWidth = vm->width;
		m_nHeight = vm->height;

		m_glWindow = glfwCreateWindow(m_nWidth, m_nHeight, m_sAppName.c_str(), m_glMonitor, NULL);

		glfwSetWindowMonitor(m_glWindow, m_glMonitor,
			0, 0, m_nWidth, m_nHeight, vm->refreshRate);
	}
	else
		m_glWindow = glfwCreateWindow(m_nWidth, m_nHeight, m_sAppName.c_str(), NULL, NULL);

	if (!m_glWindow)
	{
		const char* err;
		glfwGetError(&err);
		
		m_sErrMsg = WINDOW_PREFIX + err;

		return false;
	}

	glfwMakeContextCurrent(m_glWindow);

	int ok = glewInit();

	if (ok != GLEW_OK)
		m_sErrMsg = WINDOW_PREFIX + std::string((const char*)glewGetErrorString(ok));
	
	glViewport(0, 0, m_nWidth, m_nHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, (double)m_fZNear, (double)m_fZFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (!m_bDirtyPixel)
	{
		glEnable(GL_TEXTURE_2D);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	return true;
}

const std::string& cWindow::GetErrMessage() const
{
	return m_sErrMsg;
}

GLFWwindow* cWindow::GetGLFWwindow() const
{
	return m_glWindow;
}

bool cWindow::VSync() const
{
	return m_bVSync;
}

bool cWindow::FullScreen() const
{
	return m_bFullScreen;
}

bool cWindow::DirtyPixel() const
{
	return m_bDirtyPixel;
}

void cWindow::SetIcon(uint8_t* data, int width, int height)
{
	GLFWimage img[1];

	img[0].width = width;
	img[0].height = height;

	img[0].pixels = data;

	glfwSetWindowIcon(m_glWindow, 1, img);
}

int cWindow::GetScreenWidth() const
{
	return m_nWidth;
}

int cWindow::GetScreenHeight() const
{
	return m_nHeight;
}

const vi2d& cWindow::GetScreenSize() const
{
	return vi2d(m_nWidth, m_nHeight);
}
