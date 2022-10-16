#pragma once

#include <cstdlib>
#include "Vec.h"

class cPerlinNoise
{
public:
	cPerlinNoise() = default;
	~cPerlinNoise();

private:
	int m_nWidth;
	int m_nHeight;

	float m_fScaleBias;
	int m_nOctaves;

	float* m_fPerlinNoise2D;
	float* m_fPerlinSeed2D;

public:
	void Prepare();
	void Generate();

	float GetValue(int x, int y) const;

	void SetScaleBias(float scale_bias);
	void SetOctaves(int octaves);

	float GetScaleBias() const;
	int GetOctaves() const;

	void SetWidth(int width);
	void SetHeight(int height);

	void SetSize(const vi2d& size);

	int GetWidth() const;
	int GetHeight() const;

	vi2d GetSize() const;

};
