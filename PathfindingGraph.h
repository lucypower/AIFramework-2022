#pragma once
#include "WaypointManager.h"
#include "Waypoint.h"

using namespace std;

class PathfindingGraph
{
public:

	PathfindingGraph();
	~PathfindingGraph();

	unordered_map<Waypoint*, Waypoint*> Search(Waypoint* current, Waypoint* target);
	void AddEdge(int list, int a);

private:

	WaypointManager m_waypointManager;

	priority_queue<Waypoint*, std::vector<Waypoint*>, std::greater<Waypoint*>> frontier; // std::greater might be float for cost of path ?
	unordered_map<Waypoint*, Waypoint*> came_from;

	int vertices;

	list<int>* adj; // pointer to array containing adjacency lists

	bool* visited = new bool[vertices];
};

