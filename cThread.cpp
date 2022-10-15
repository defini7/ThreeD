#include "cThread.h"

cThread::cThread()
{
	for (int i = 0; i < 512; i++)
		m_ksKeys[i] = { false, false, false };

	for (int i = 0; i < 5; i++)
		m_ksMouse[i] = { false, false, false };

	for (int i = 0; i < 512; i++)
		m_nKeyOldState[i] = 0;
	
	for (int i = 0; i < 5; i++)
		m_nMouseOldState[i] = 0;

	for (int i = 0; i < 512; i++)
		m_nKeyNewState[i] = 0;
}

cThread::~cThread()
{
}

bool cThread::Run(cWindow& wnd)
{	
	m_fDeltaTime = std::chrono::duration<float>(m_tpEnd - m_tpStart).count();
	m_tpStart = std::chrono::system_clock::now();

	if (glfwWindowShouldClose(wnd.GetGLFWwindow()))
		return false;

	for (int i = 0; i < 512; i++)
	{
		m_nKeyNewState[i] = glfwGetKey(wnd.GetGLFWwindow(), i);

		m_ksKeys[i].bPressed = false;
		m_ksKeys[i].bReleased = false;

		if (m_nKeyNewState[i] != m_nKeyOldState[i])
		{
			if (m_nKeyNewState[i])
			{
				m_ksKeys[i].bPressed = !m_ksKeys[i].bHeld;
				m_ksKeys[i].bHeld = true;
			}
			else
			{
				m_ksKeys[i].bReleased = true;
				m_ksKeys[i].bHeld = false;
			}
		}

		m_nKeyOldState[i] = m_nKeyNewState[i];
	}

	for (int i = 0; i < 5; i++)
	{
		m_nMouseNewState[i] = glfwGetMouseButton(wnd.GetGLFWwindow(), i);

		m_ksMouse[i].bPressed = false;
		m_ksMouse[i].bReleased = false;

		if (m_nMouseNewState[i] != m_nMouseOldState[i])
		{
			if (m_nMouseNewState[i])
			{
				m_ksMouse[i].bPressed = true;
				m_ksMouse[i].bHeld = true;
			}
			else
			{
				m_ksMouse[i].bReleased = true;
				m_ksMouse[i].bHeld = false;
			}
		}

		m_nMouseOldState[i] = m_nMouseNewState[i];
	}
	
	double dMouseX, dMouseY;

	glfwGetCursorPos(wnd.GetGLFWwindow(), &dMouseX, &dMouseY);

	m_nMouseX = (int)dMouseX;
	m_nMouseY = (int)dMouseY;
	
	return true;
}

float cThread::GetDeltaTime() const
{
	return m_fDeltaTime;
}

int cThread::GetMouseX() const
{
	return m_nMouseX;
}

int cThread::GetMouseY() const
{
	return m_nMouseY;
}

const vi2d& cThread::GetMouse() const
{
	return vi2d(m_nMouseX, m_nMouseY);
}

KeyState cThread::GetKey(short k) const
{
	return m_ksKeys[k];
}

KeyState cThread::GetMouse(short m) const
{
	return m_ksMouse[m];
}

void cThread::Refresh(cWindow& wnd)
{
	if (wnd.VSync())
		glfwSwapBuffers(wnd.GetGLFWwindow());
	else
		glFlush();

	glfwPollEvents();

	m_tpEnd = std::chrono::system_clock::now();
}
