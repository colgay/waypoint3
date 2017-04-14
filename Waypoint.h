#pragma once

#include <vector>
#include <memory>
#include <algorithm>

class Waypoint;

struct Neighbor
{
	std::shared_ptr<Waypoint> pWaypoint;
	int flags;
};


class Waypoint
{
public:
	Waypoint(const Vector &origin, float radius, int flags);
	~Waypoint();

	float GetRadius(void) const { return m_radius; }
	int GetFlags(void) const { return m_flags; }
	void AddFlag(int flag) { m_flags |= flag; }
	void RemoveFlag(int flag) { m_flags &= ~flag; }
	void SetFlags(int flags) { m_flags = flags; }
	const Vector *GetPosition(void) const { return &m_position; }

	typedef std::vector<std::shared_ptr<Neighbor>> NeighborList;
	const NeighborList &GetNeighbors(void) const { return m_neighbors; }
	void AddNeighbor(std::shared_ptr<Waypoint> pWaypoint, int flags);
	void RemoveNeighbor(std::shared_ptr<Waypoint> pWaypoint);
	bool IsNeighborSet(std::shared_ptr<Waypoint> pWaypoint) const;
	int FindNeighborAt(std::shared_ptr<Waypoint> pWaypoint) const;

	void AddNeighborFlag(std::shared_ptr<Waypoint> pWaypoint, int flag);
	void RemoveNeighborFlag(std::shared_ptr<Waypoint> pWaypoint, int flag);
	void SetNeighborFlags(std::shared_ptr<Waypoint> pWaypoint, int flags);

	float DistTo(std::shared_ptr<Waypoint> pWaypoint) const
	{
		return (m_position - *(pWaypoint->GetPosition())).Length();
	}

private:

	NeighborList m_neighbors;
	int m_flags;
	float m_radius;
	Vector m_position;
};