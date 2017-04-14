#include "extdll.h"
#include "Cmd.h"

static std::vector<Cmd> s_Cmds;

Cmd::Cmd(const char *pszName, const char *pszInfo, CmdCallback_t pfnCmdCallback)
	: m_strName(pszName), m_strInfo(pszInfo)
{
	m_pfnCmdCallback = pfnCmdCallback;

	s_Cmds.push_back(*this);
}

Cmd::~Cmd(void)
{
}

void HandleCommands(const char *pszCmd)
{
	for (int i = 0; i < s_Cmds.size; i++)
	{

	}
}