#pragma once
#include "WaypointManager.h"

struct Waypoint
{
	int data;
};

class PathfindingGraph
{
public:

	PathfindingGraph();
	~PathfindingGraph();

	bool Search();

private:

	WaypointManager m_waypointManager;

	queue<Waypoint> frontier;
	unordered_map<Waypoint*, Waypoint*> came_from;
};

