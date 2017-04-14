#pragma once

#include <vector>
#include <memory>

class Waypoint;

class Map
{
public:
	Map();
	~Map();

	std::shared_ptr<Waypoint> CreateWaypoint(const Vector &origin, float radius, int flags);
	void RemoveWaypoint(std::shared_ptr<Waypoint> pWaypoint);

	const std::vector<std::shared_ptr<Waypoint>> &GetWaypoints(void) const { return m_waypoints; }
	int GetWaypointIndex(std::shared_ptr<Waypoint> pWaypoint) const;

	std::shared_ptr<Waypoint> GetNearestWaypoint(const Vector &origin, float maxRadius) const;

private:
	std::vector<std::shared_ptr<Waypoint>> m_waypoints;
};

