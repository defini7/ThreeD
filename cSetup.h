#pragma once

#include "GlfwSetup.h"

#include <string>

#define SETUP_PREFIX std::string("Setup: ")

class cSetup
{
public:
	cSetup();
	~cSetup();

private:
	int m_nErrCode;
	std::string m_sErrMsg;

public:
	int GetErrCode() const;
	const std::string& GetErrMessage() const;

};
