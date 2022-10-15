#include "cCamera.h"

cCamera::cCamera()
{
	vPos = vf3d(0.0f, 0.0f, 0.0f);
	vRot = vf3d(0.0f, 0.0f, 0.0f);
}


cCamera::cCamera(float x, float y, float z, float rx, float ry, float rz)
{
	vPos = vf3d(x, y, z);
	vRot = vf3d(rx, ry, rz);
}


cCamera::cCamera(const vf3d& pos, const vf3d& rot)
{
	vPos = pos;
	vRot = rot;
}

void cCamera::Apply(cWindow& wnd, cThread& thrd)
{
	if (glfwGetWindowAttrib(wnd.GetGLFWwindow(), GLFW_FOCUSED))
	{
		float fAngle = -vRot.z / 180.0f * (float)M_PI;
		float fSpeed = 0.0f;

		if (thrd.GetKey(GLFW_KEY_SPACE).bHeld) vPos.z += 100.0f * thrd.GetDeltaTime();
		if (thrd.GetKey(GLFW_KEY_LEFT_SHIFT).bHeld) vPos.z -= 100.0f * thrd.GetDeltaTime();

		if (thrd.GetKey(GLFW_KEY_W).bHeld) fSpeed = 1.1f;
		if (thrd.GetKey(GLFW_KEY_S).bHeld) fSpeed = -1.1f;
		if (thrd.GetKey(GLFW_KEY_A).bHeld) { fSpeed = 1.0f; fAngle -= (float)M_PI_2; }
		if (thrd.GetKey(GLFW_KEY_D).bHeld) { fSpeed = 1.0f; fAngle += (float)M_PI_2; }

		if (fSpeed != 0.0f)
		{
			vPos.x += sinf(fAngle) * fSpeed;
			vPos.y += cosf(fAngle) * fSpeed;
		}

		auto rotate = [&](float x, float z)
		{
			vRot.z += z;
			if (vRot.z < 0.0f) vRot.z += 360.0f;
			if (vRot.z > 360.0f) vRot.z -= 360.0f;

			vRot.x += x;
			if (vRot.x < -90.0f) vRot.x = -90.0f;
			if (vRot.x > 180.0f) vRot.x = 180.0f;
		};

		vi2d vBase = wnd.GetScreenSize() / 2;
		vi2d vMouse = thrd.GetMouse();

		rotate((vBase.y - vMouse.y) / 5.0f, (vBase.x - vMouse.x) / 5.0f);
		glfwSetCursorPos(wnd.GetGLFWwindow(), (double)vBase.x, (double)vBase.y);
	}
}

void cCamera::Rotate()
{
	glRotatef(-vRot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(-vRot.z, 0.0f, 0.0f, 1.0f);
}

void cCamera::Translate()
{
	glTranslatef(-vPos.x, -vPos.y, -vPos.z);
}
