#include "PathfindingGraph.h"

PathfindingGraph::PathfindingGraph()
{

}

PathfindingGraph::~PathfindingGraph()
{

}

bool PathfindingGraph::Search()
{
	Waypoint* start = new Waypoint();

	while (frontier != empty)
	{
		Waypoint* current = frontier front;
		frontier.pop();
		
		Waypoint* wp = m_waypointManager->getNeighbouringWaypoints(current);

		if (current == goal)
		{
			break;
		}

		for (Waypoint neighbours in wp)
		{

		}
	}
}