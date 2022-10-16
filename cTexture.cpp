#define STB_IMAGE_IMPLEMENTATION
#include "cTexture.h"

cTexture::cTexture()
{
}

cTexture::~cTexture()
{
	stbi_image_free(m_cData);
	glDeleteTextures(1, &m_nTextureId);
}

bool cTexture::LoadData(const std::string& filename, bool flip)
{
	m_sFilename = filename;

	if (!std::filesystem::exists(m_sFilename))
	{
		m_sErrMsg = IMAGE_LOADER_PREFIX + "file does not exist";
		return false;
	}

	stbi_set_flip_vertically_on_load((int)flip);
	m_cData = stbi_load(m_sFilename.c_str(), &m_nWidth, &m_nHeight, &m_nChannels, 0);

	if (!m_cData)
	{
		m_sErrMsg = STB_IMAGE_PREFIX + stbi_failure_reason();
		return false;
	}

	return true;
}

bool cTexture::LoadTexture()
{
	unsigned int nFormat = 0;

	if (m_nChannels == 3)
		nFormat = GL_RGB;
	else if (m_nChannels == 4)
		nFormat = GL_RGBA;
	else
	{
		m_sErrMsg = IMAGE_LOADER_PREFIX + "unsupported amount of channels";
		return false;
	}

	glGenTextures(1, &m_nTextureId);
	glBindTexture(GL_TEXTURE_2D, m_nTextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		nFormat,
		m_nWidth,
		m_nHeight,
		0,
		nFormat,
		GL_UNSIGNED_BYTE,
		m_cData
	);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void cTexture::SetData(unsigned char* data)
{
	for (int i = 0; i < m_nWidth * m_nHeight * m_nChannels; i++)
		m_cData[i] = data[i];
}

void cTexture::SetPixel(int x, int y, unsigned char rgba[4])
{
	m_cData[m_nChannels * (y * m_nWidth + x) + 0] = rgba[0];
	m_cData[m_nChannels * (y * m_nWidth + x) + 1] = rgba[1];
	m_cData[m_nChannels * (y * m_nWidth + x) + 2] = rgba[2];
	
	if (m_nChannels == 4)
		m_cData[m_nChannels * (y * m_nWidth + x) + 3] = rgba[3];
}

const unsigned char* cTexture::GetPixel(int x, int y)
{
	if (x < 0 || y < 0 || x >= m_nWidth || y >= m_nHeight)
		return nullptr;

	unsigned char rgba[4] = {
		m_cData[m_nChannels * (y * m_nWidth + x) + 0],
		m_cData[m_nChannels * (y * m_nWidth + x) + 1],
		m_cData[m_nChannels * (y * m_nWidth + x) + 2],
	};

	rgba[3] = (m_nChannels == 4) ? m_cData[m_nChannels * (y * m_nWidth + x) + 3] : 255;

	return rgba;
}

const unsigned char* cTexture::Sample(float x, float y)
{
	int sx = std::min(int(x * (float)m_nWidth), m_nWidth - 1);
	int sy = std::min(int(y * (float)m_nHeight), m_nHeight - 1);
	return GetPixel(sx, sy);
}

int cTexture::GetWidth() const
{
	return m_nWidth;
}

int cTexture::GetHeight() const
{
	return m_nHeight;
}

int cTexture::GetChannels() const
{
	return m_nChannels;
}

const std::string& cTexture::GetFilename() const
{
	return m_sFilename;
}

const std::string& cTexture::GetErrMessage() const
{
	return m_sErrMsg;
}

unsigned char* cTexture::GetData() const
{
	return m_cData;
}

void cTexture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_nTextureId);
}

void cTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int cTexture::GetId() const
{
	return m_nTextureId;
}
