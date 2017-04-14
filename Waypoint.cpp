#include "extdll.h"

#include "Waypoint.h"

Waypoint::Waypoint(const Vector &origin, float radius, int flags)
{
	m_position = origin;
	m_radius = radius;
	m_flags = flags;
}


Waypoint::~Waypoint()
{
}

int Waypoint::FindNeighborAt(std::shared_ptr<Waypoint> pWaypoint) const
{
	auto pred = [pWaypoint](const std::shared_ptr<Neighbor> & neighbor) {
		return neighbor->pWaypoint == pWaypoint;
	};

	std::vector<std::shared_ptr<Neighbor>>::const_iterator it;
	it = std::find_if(m_neighbors.cbegin(), m_neighbors.cend(), pred);

	if (it == m_neighbors.cend())
		return -1;

	return std::distance(m_neighbors.begin(), it);
}

bool Waypoint::IsNeighborSet(std::shared_ptr<Waypoint> pWaypoint) const
{
	return FindNeighborAt(pWaypoint) != -1;
}

void Waypoint::AddNeighbor(std::shared_ptr<Waypoint> pWaypoint, int flags)
{
	if (IsNeighborSet(pWaypoint))
		return;

	std::shared_ptr<Neighbor> pNeighbor;
	pNeighbor->pWaypoint = pWaypoint;
	pNeighbor->flags = flags;

	m_neighbors.push_back(pNeighbor);
}

void Waypoint::RemoveNeighbor(std::shared_ptr<Waypoint> pWaypoint)
{
	this->m_neighbors.erase(m_neighbors.begin() + FindNeighborAt(pWaypoint));
}

void Waypoint::AddNeighborFlag(std::shared_ptr<Waypoint> pWaypoint, int flag)
{
	int pos = FindNeighborAt(pWaypoint);
	if (pos == -1)
		return;

	m_neighbors[pos]->flags |= flag;
}

void Waypoint::RemoveNeighborFlag(std::shared_ptr<Waypoint> pWaypoint, int flag)
{
	int pos = FindNeighborAt(pWaypoint);
	if (pos == -1)
		return;

	m_neighbors[pos]->flags &= ~flag;
}

void Waypoint::SetNeighborFlags(std::shared_ptr<Waypoint> pWaypoint, int flags)
{
	int pos = FindNeighborAt(pWaypoint);
	if (pos == -1)
		return;

	m_neighbors[pos]->flags = flags;
}