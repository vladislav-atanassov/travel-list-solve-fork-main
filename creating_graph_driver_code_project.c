#include <stdio.h>

#include "print_solution.h"
#include "dynamic_graph_creation.h"
#include "dijkstra_algorithm.h"
#include "accept_arrow_input.h"

int main() 
{	
    int vertices = get_vertices();

    struct Graph* graph = dynamic_graph_creation(vertices);

    dijkstra_algorithm(graph, accept_arrow_input(graph, vertices), vertices);

    free_memory(graph);

    return 0;
}
