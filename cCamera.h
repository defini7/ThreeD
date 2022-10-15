#pragma once

#include "Vec.h"
#include "cWindow.h"
#include "cCamera.h"
#include "cThread.h"

#include <cmath>

class cCamera
{
public:
	cCamera();
	cCamera(float x, float y, float z, float rx = 0.0f, float ry = 0.0f, float rz = 0.0f);
	cCamera(const vf3d& pos, const vf3d& rofloat = vf3d(0.0f, 0.0f, 0.0f));

public:
	vf3d vPos;
	vf3d vRot;

public:
	void Apply(cWindow& wnd, cThread& thrd);
	void Rotate();
	void Translate();

};
