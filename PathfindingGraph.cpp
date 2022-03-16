#include "PathfindingGraph.h"

PathfindingGraph::PathfindingGraph()
{

}

PathfindingGraph::~PathfindingGraph()
{

}

void PathfindingGraph::AddEdge(int list, int a)
{
	adj[list].push_back(a);
}

void PathfindingGraph::Search(Waypoint* current)
{
	for (int i = 0; i < vertices; i++)
		visited[i] = false;

	while (!frontier.empty())
	{
		current = frontier.front();
		frontier.pop();
		
		vecWaypoints wp = m_waypointManager.getNeighbouringWaypoints(current);

		for (Waypoint* neighbours : wp)
		{
			if (!neighbours)
			{
				frontier.push(neighbours);
				came_from <neighbours, current>;
			}
		}
	}

}