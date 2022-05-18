#include <SFML/Graphics.hpp>
#include "matrix_app.h"
#include "Graph.h"
#include "Turtle.h"
#include "voyager_task.h"
#include <iostream>
#include <vector>


using namespace std;



int main() 
{


	Graph<string> graph;
	for (int i = 1; i <= 6; ++i) 
	{
		graph.insertVertex(std::to_string(i));
	}
	graph.InsertEdge("2", "1", 28);
	graph.InsertEdge("6", "1",18);
	graph.InsertEdge("1", "4",15);
	graph.InsertEdge("1", "3", 13);
	graph.InsertEdge("4", "6", 31);
	graph.InsertEdge("5", "4", 39);
	graph.InsertEdge("4", "5", 39);
	graph.InsertEdge("2", "4", 20);
	graph.InsertEdge("5", "2", 21);
	graph.InsertEdge("3", "5", 30);
	graph.InsertEdge("3", "6", 40);
	graph.InsertEdge("5", "6", 12);
	graph.InsertEdge("6", "3", 12);

	graph.StartApplication();
	return 0;


}
