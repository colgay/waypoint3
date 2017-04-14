#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> ParameterList;
typedef void(*CmdCallback_t)(const ParameterList &commands);

class Cmd
{
public:
	Cmd(const char *pszName, const char *pszInfo, CmdCallback_t pfnCmdCallback);
	~Cmd(void);

private:
	std::string m_strName;
	std::string m_strInfo;

	CmdCallback_t m_pfnCmdCallback;
};

void HandleCommands(const char *pszCmd);