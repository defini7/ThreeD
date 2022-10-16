#include "cPerlinNoise.h"

cPerlinNoise::~cPerlinNoise()
{
	delete[] m_fPerlinNoise2D;
	delete[] m_fPerlinSeed2D;
}

void cPerlinNoise::Prepare()
{
	m_fPerlinNoise2D = new float[m_nWidth * m_nHeight];
	m_fPerlinSeed2D = new float[m_nWidth * m_nHeight];

	for (int i = 0; i < m_nWidth * m_nHeight; i++)
		m_fPerlinSeed2D[i] = (float)rand() / (float)RAND_MAX;

	m_nOctaves = 12;
	m_fScaleBias = 2.0f;
}

void cPerlinNoise::Generate()
{
	for (int x = 0; x < m_nWidth; x++)
		for (int y = 0; y < m_nHeight; y++)
		{
			float fNoise = 0.0f;
			float fScale = 1.0f;
			float fScaleAccumulator = 0.0f;

			for (int o = 0; o < m_nOctaves; o++)
			{
				int nPitch = m_nWidth >> o;

				if (nPitch)
				{
					int nSampleX1 = (x / nPitch) * nPitch;
					int nSampleY1 = (y / nPitch) * nPitch;

					int nSampleX2 = (nSampleX1 + nPitch) % m_nWidth;
					int nSampleY2 = (nSampleY1 + nPitch) % m_nWidth;

					float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
					float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

					float fSampleT = (1.0f - fBlendX) * m_fPerlinSeed2D[nSampleY1 * m_nWidth + nSampleX1] + fBlendX * m_fPerlinSeed2D[nSampleY1 * m_nWidth + nSampleX2];
					float fSampleB = (1.0f - fBlendX) * m_fPerlinSeed2D[nSampleY2 * m_nWidth + nSampleX1] + fBlendX * m_fPerlinSeed2D[nSampleY2 * m_nWidth + nSampleX2];

					fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
					fScaleAccumulator += fScale;
					fScale /= m_fScaleBias;
				}
			}

			m_fPerlinNoise2D[y * m_nWidth + x] = fNoise / fScaleAccumulator;
		}

}

float cPerlinNoise::GetValue(int x, int y) const
{
	return m_fPerlinNoise2D[y * m_nWidth + x];
}

void cPerlinNoise::SetScaleBias(float scale_bias)
{
	m_fScaleBias = scale_bias;
}

void cPerlinNoise::SetOctaves(int octaves)
{
	m_nOctaves = octaves;
}

float cPerlinNoise::GetScaleBias() const
{
	return m_fScaleBias;
}

int cPerlinNoise::GetOctaves() const
{
	return m_nOctaves;
}

void cPerlinNoise::SetWidth(int width)
{
	m_nWidth = width;
}

void cPerlinNoise::SetHeight(int height)
{
	m_nHeight = height;
}

void cPerlinNoise::SetSize(const vi2d& size)
{
	m_nWidth = size.x;
	m_nHeight = size.y;
}

int cPerlinNoise::GetWidth() const
{
	return m_nWidth;
}

int cPerlinNoise::GetHeight() const
{
	return m_nHeight;
}

vi2d cPerlinNoise::GetSize() const
{
	return vi2d(m_nWidth, m_nHeight);
}
