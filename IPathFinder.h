#pragma once

#include <memory>

class Waypoint;
class Path;
class Map;

class IPathFinder
{
public:
	IPathFinder(void);
	virtual ~IPathFinder(void);
	virtual const Path *CalcPath(const std::shared_ptr<Waypoint> start, const std::shared_ptr<Waypoint> dest) const = 0;
	virtual void AssignToMap(Map *pMap) = 0;
	virtual void Clear(void) = 0;
};