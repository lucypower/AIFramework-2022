#pragma once
#include "WaypointManager.h"
#include "Waypoint.h"

class PathfindingGraph
{
public:

	PathfindingGraph();
	~PathfindingGraph();

	void Search(Waypoint* a);
	void AddEdge(int list, int a);

private:

	WaypointManager m_waypointManager;

	queue<Waypoint*> frontier;
	unordered_map<Waypoint*, Waypoint*> came_from;

	int vertices;

	list<int>* adj; // pointer to array containing adjacency lists

	bool* visited = new bool[vertices];
};

