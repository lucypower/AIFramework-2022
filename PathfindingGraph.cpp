#include "PathfindingGraph.h"

PathfindingGraph::PathfindingGraph()
{

}

PathfindingGraph::~PathfindingGraph()
{

}

//void PathfindingGraph::AddEdge(int list, int a)
//{
//	adj[list].push_back(a);
//}

unordered_map<Waypoint*, Waypoint*> PathfindingGraph::Search(Waypoint* current, Waypoint* target)
{
	/*for (int i = 0; i < vertices; i++)
		visited[i] = false;

	visited[current] = true;
	frontier.push_back(current);*/
	Waypoint* start = current;
	frontier.push(start);

	//while (!frontier.empty())
	//{
	//	current = frontier.front();
	//	frontier.pop();
	//	
	//	if (current == target)
	//		break;

	//	vecWaypoints wp = m_waypointManager.getNeighbouringWaypoints(current);
	//	//Waypoint* wp = m_waypointManager.getNearestWaypoint(current);

	//	for_each (came_from.begin(), came_from.end(), make_pair(wp, start));
	//	{
	//		if (came_from.find(wp) != came_from.end())
	//		{
	//			frontier.push(wp);
	//			came_from <wp, current>;
	//		}
	//	}
	//}

	//TODO: change queue to priority queue and set up containers which will then order in terms of cost and then should work or something like that idk xD

	return came_from;
}