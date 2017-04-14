#include "amxxmodule.h"

#include <stdlib.h>

#include "Waypoint.h"
#include "Map.h"
#include "Cmd.h"

static Map s_Map;
edict_t *g_editor = nullptr;
short g_sprite;

//static Cmd create("create", "Creates a Waypoint", xxx);

void OnPluginsLoaded(void)
{
	g_sprite = PRECACHE_MODEL("sprites/zbeam4.spr");
}

void OnAmxxAttach(void)
{
}

void OnAmxxDetach(void)
{
}

void OnClientCommand(edict_t *pEntity)
{
	const char *cmd = CMD_ARGV(0);
	
	if (strcmp(cmd, "wp") == 0)
	{
		cmd = CMD_ARGV(1);

		if (strcmp(cmd, "editor") == 0)
		{
			if (atoi(CMD_ARGV(2))) // on
			{
				g_editor = pEntity;
				UTIL_ClientPrintAll(HUD_PRINTTALK, "* Waypoint editor is ON.");
			}
			else // off
			{
				g_editor = nullptr;
				UTIL_ClientPrintAll(HUD_PRINTTALK, "* Waypoint editor is OFF.");
			}

			RETURN_META(MRES_SUPERCEDE);
		}
		else if (strcmp(cmd, "create") == 0)
		{
			if (g_editor != pEntity)
				RETURN_META(MRES_SUPERCEDE);

			const char *args[2];
			args[0] = CMD_ARGV(2);
			args[1] = CMD_ARGV(3);
			
			float radius = atof(args[0]);
			int flags = atoi(args[1]);

			const Vector &origin = pEntity->v.origin;
			
			std::shared_ptr<Waypoint> pWaypoint = s_Map.CreateWaypoint(origin, radius, flags);
			if (pWaypoint != nullptr)
			{
				UTIL_ClientPrintAll(HUD_PRINTTALK, UTIL_VarArgs("* Create waypoint #%d\n", s_Map.GetWaypointIndex(pWaypoint)));
			}

			RETURN_META(MRES_SUPERCEDE);
		}
		else if (strcmp(cmd, "remove") == 0)
		{
			if (g_editor != pEntity)
				RETURN_META(MRES_SUPERCEDE);

			const Vector &origin = pEntity->v.origin;

			std::shared_ptr<Waypoint> pWaypoint = s_Map.GetNearestWaypoint(origin, 100);
			
			if (pWaypoint == nullptr)
				UTIL_ClientPrintAll(HUD_PRINTTALK, "Cannot find nearby waypoint.");
			else
			{
				int index = s_Map.GetWaypointIndex(pWaypoint);
				s_Map.RemoveWaypoint(pWaypoint);
				UTIL_ClientPrintAll(HUD_PRINTTALK, UTIL_VarArgs("* Remove waypoint #%d\n", index));
			}

			RETURN_META(MRES_SUPERCEDE);
		}
	}

	RETURN_META(MRES_IGNORED);
}

void OnPlayerPreThink(edict_t *pEntity)
{
	if (g_editor == pEntity)
	{
		static float lastUpdateTime = 0.0f;
		if (gpGlobals->time < lastUpdateTime + 0.5)
			RETURN_META(MRES_IGNORED);

		const Vector &origin = pEntity->v.origin;

		std::vector<std::shared_ptr<Waypoint>> waypoints = s_Map.GetWaypoints();

		// There is no waypoint
		if (waypoints.size() == 0)
			RETURN_META(MRES_IGNORED);

		// Sort the waypoints
		std::sort(waypoints.begin(), waypoints.end(), [origin](const std::shared_ptr<Waypoint> &lhs, const std::shared_ptr<Waypoint> &rhs) {
			return (origin - *(lhs->GetPosition())).Length() < (origin - *(rhs->GetPosition())).Length();
		});

		// Show only max 60 waypoints
		int size = min(waypoints.size(), 60);

		for (std::vector<std::shared_ptr<Waypoint>>::const_iterator it = waypoints.cbegin(); it != waypoints.cbegin() + size; ++it)
		{
			std::shared_ptr<Waypoint> pPoint = *it;

			// Show a waypoint
			MESSAGE_BEGIN(MSG_ONE_UNRELIABLE, SVC_TEMPENTITY, NULL, pEntity);
				WRITE_BYTE(TE_BEAMPOINTS);
				WRITE_COORD(pPoint->GetPosition()->x);
				WRITE_COORD(pPoint->GetPosition()->y);
				WRITE_COORD(pPoint->GetPosition()->z - 36);
				WRITE_COORD(pPoint->GetPosition()->x);
				WRITE_COORD(pPoint->GetPosition()->y);
				WRITE_COORD(pPoint->GetPosition()->z + 36);
				WRITE_SHORT(g_sprite);
				WRITE_BYTE(0);		// framerate
				WRITE_BYTE(0);		// framerate
				WRITE_BYTE(5);		// life
				WRITE_BYTE(10);		// width
				WRITE_BYTE(0);		// noise
				WRITE_BYTE(0);		// r
				WRITE_BYTE(255);	// g
				WRITE_BYTE(0);		// b
				WRITE_BYTE(200);	// brightness
				WRITE_BYTE(0);		// speed
			MESSAGE_END();
		}

		lastUpdateTime = gpGlobals->time;
	}

	RETURN_META(MRES_IGNORED);
}

/*
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
*/