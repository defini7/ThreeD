#pragma once

#include "GlfwSetup.h"

#include <stb_image.h>

#include <string>
#include <filesystem>

#define IMAGE_LOADER_PREFIX std::string("cImageLoader: ")
#define STB_IMAGE_PREFIX std::string("stb_image: ")

class cTexture
{
public:
	cTexture();
	~cTexture();

private:
	int m_nWidth;
	int m_nHeight;
	int m_nChannels;

	std::string m_sFilename;

	unsigned char* m_cData;

	std::string m_sErrMsg;

	unsigned int m_nTextureId;

public:
	bool LoadData(const std::string& filename, bool flip = false);
	bool LoadTexture();

	void SetData(unsigned char* data);
	void SetPixel(int x, int y, unsigned char rgba[4]);

	const unsigned char* GetPixel(int x, int y);
	const unsigned char* Sample(float x, float y);

	int GetWidth() const;
	int GetHeight() const;
	int GetChannels() const;
	unsigned int GetId() const;

	const std::string& GetFilename() const;
	const std::string& GetErrMessage() const;

	unsigned char* GetData() const;

	void Bind();
	void Unbind();
	
};
