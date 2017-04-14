#pragma once

#include <memory>

class Waypoint;
class Path;

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	void SetStart(const std::shared_ptr<Waypoint> &start) { m_start = start; }
	void SetGoal(const std::shared_ptr<Waypoint> &goal) { m_goal = goal; }

	std::shared_ptr<Waypoint> GetStart(void) const { return m_start; }
	std::shared_ptr<Waypoint> GetGoal(void) const { return m_goal; }

	template <class TAlgorithm>
	std::shared_ptr<Path> FindPath(void) const
	{
		TAlgorithm &algorithm = TAlgorithm::GetInstance();
		return algorithm.CalcPath(m_start, m_goal);
	}
private:
	std::shared_ptr<Waypoint> m_start;
	std::shared_ptr<Waypoint> m_goal;
};

