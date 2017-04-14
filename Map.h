#pragma once

#include <vector>
#include <memory>

class Waypoint;

class Map
{
public:
	Map();
	~Map();

	void CreateWaypoint(const Vector &origin, float radius, int flags);
	void RemoveWaypoint(std::shared_ptr<Waypoint> pWaypoint);

	const std::vector<std::shared_ptr<Waypoint>> &GetWaypoints(void) const { return m_waypoints; }
	std::shared_ptr<Waypoint> GetWaypointAt(int index) const;

	std::shared_ptr<Waypoint> GetNearestWaypoint(const Vector &origin, float maxRadius) const;

private:
	std::vector<std::shared_ptr<Waypoint>> m_waypoints;
};

