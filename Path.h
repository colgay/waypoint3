#pragma once

#include <vector>
#include <memory>

class Waypoint;

class Path
{
public:
	Path();
	~Path();

	std::shared_ptr<Waypoint> GetCurrent() { return m_waypoints[m_current]; }
	std::shared_ptr<Waypoint> GetNext() { return m_waypoints[++m_current]; }

	void ClearWaypoints() { m_waypoints.clear(); }
	void PushWaypoint(std::shared_ptr<Waypoint> pWaypoint) { m_waypoints.push_back(pWaypoint); }

private:
	std::vector<std::shared_ptr<Waypoint>> m_waypoints;

	int m_current;
};