#include "amxxmodule.h"

#include "Waypoint.h"
#include "Map.h"

static Map s_Map;

void OnAmxxAttach(void)
{
	// how to create an object, an? a? ha

}


void OnAmxxDetach(void)
{
	// how to delete an object ?
}


// command handling

void FN_ClientCommand(edict_t *pEntity)
{
	{
		const char *pszCmd = CMD_ARGS();
		HandleCommands(pszCmd);
	}
}

void FN_ServerCommand(const char *pszCmd)
{
	{
		HandleCommands(pszCmd);
	}
}