#include "extdll.h"

#include "Waypoint.h"
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

std::shared_ptr<Waypoint> Map::CreateWaypoint(const Vector &origin, float radius, int flags)
{
	std::shared_ptr<Waypoint> pWaypoint = std::shared_ptr<Waypoint>(new Waypoint(origin, radius, flags));
	m_waypoints.push_back(pWaypoint);

	return pWaypoint;
}

void Map::RemoveWaypoint(std::shared_ptr<Waypoint> pWaypoint)
{
	m_waypoints.erase(std::remove(m_waypoints.begin(), m_waypoints.end(), pWaypoint), m_waypoints.end());
}

int Map::GetWaypointIndex(std::shared_ptr<Waypoint> pWaypoint) const
{
	std::vector<std::shared_ptr<Waypoint>>::const_iterator it;
	it = std::find(m_waypoints.cbegin(), m_waypoints.cend(), pWaypoint);

	return std::distance(m_waypoints.cbegin(), it);
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