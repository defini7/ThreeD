#include "cSetup.h"

cSetup::cSetup()
{
	m_nErrCode = glfwInit();

	if (!m_nErrCode)
	{
		const char* msg;
		glfwGetError(&msg);
		m_sErrMsg = SETUP_PREFIX + std::string(msg);
		return;
	}
}

cSetup::~cSetup()
{
	glfwTerminate();
}

int cSetup::GetErrCode() const
{
	return m_nErrCode;
}

const std::string& cSetup::GetErrMessage() const
{
	return m_sErrMsg;
}
