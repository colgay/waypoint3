#include "extdll.h"

#include "Waypoint.h"
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::CreateWaypoint(const Vector &origin, float radius, int flags)
{
	std::shared_ptr<Waypoint> pWaypoint(&origin, radius, flags);
	m_waypoints.push_back(pWaypoint);
}

void Map::RemoveWaypoint(std::shared_ptr<Waypoint> pWaypoint)
{
	m_waypoints.erase(std::remove(m_waypoints.begin(), m_waypoints.end(), pWaypoint), m_waypoints.end());
}

std::shared_ptr<Waypoint> Map::GetWaypointAt(int index) const
{
	return m_waypoints[index];
}

std::shared_ptr<Waypoint> Map::GetNearestWaypoint(const Vector &origin, float maxRadius) const
{
	std::shared_ptr<Waypoint> pResult = nullptr;
	float minRadius = maxRadius;
	float dist;

	for (std::vector<std::shared_ptr<Waypoint>>::const_iterator it = m_waypoints.cbegin(); it != m_waypoints.cend(); ++it)
	{
		std::shared_ptr<Waypoint> pWaypoint = *it;
		dist = (origin - *(pWaypoint->GetPosition())).Length();

		if (dist < minRadius)
		{
			pResult = pWaypoint;
			minRadius = dist;
		}
	}

	return pResult;
}