#include "extdll.h"
#include "Cmd.h"

#include "wp_utils.h"

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

void HandleCommands(edict_t *pEntity, const char *pszCmd)
{
	std::vector<std::string> strings;

	{
		std::string strCmd = pszCmd;
		UTIL_SplitString(strCmd, strings, ' ');
	}

	for (unsigned int i = 0; i < s_Cmds.size(); i++)
	{
		if (strings[0] != s_Cmds[i].GetName())
			continue;

		/*if (strings.size == 1)
		{
			::ClientPrint(&pEntity->v, MSG_ONE, "Usage: %s\n", s_Cmds[i].GetInfo());
		}*/

		s_Cmds[i].CallCallback(strings);
		break;
	}
}

