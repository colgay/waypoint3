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

	const char *GetName(void) const { return m_strName.c_str(); }
	const char *GetInfo(void) const { return m_strInfo.c_str(); }

	void CallCallback(const ParameterList &parameterList) const { m_pfnCmdCallback(parameterList); }

private:
	std::string m_strName;
	std::string m_strInfo;

	CmdCallback_t m_pfnCmdCallback;
};

void HandleCommands(edict_t *pEntity, const char *pszCmd);