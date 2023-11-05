#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dynamic_graph_creation.h"

// Function to get the cost of the node
// The funtion takes not arguments
int get_cost(void)
{
    int cost;

    while(true)
    {
        printf("Enter cost for the node: ");
        scanf("%d", &cost);
        
        if(cost > 0) // Validating the cost of the node
        {
            return cost;
        }

        printf("Ivalid input for cost!\n");
    }
}

// Function to get the X axis position of the node
// The function takes one argument
// 1. The size of the matrix int vertices
int get_pos_x(int vertices)
{
    int position_x;

    while(true)
    {
        printf("Enter position for the edge on the X axis: ");
        scanf("%d", &position_x);
        
        // Validating out of bounds error
        if(position_x > 0 || position_x < vertices - 1) 
        {
            return position_x;
        }

        printf("Ivalid input for X axis!\n");      
    }

    printf("Done");
}

// Function to get the Y axis position of the node
// The function takes one argument
// 1. The size of the matrix int vertices
int get_pos_y(int vertices)
{
    int position_y;

    while(true)
    {
        printf("Enter position for the edge on the Y axis: ");
        scanf("%d", &position_y);
        
        // Validating out of bounds error
        if(position_y > 0 || position_y < vertices - 1) 
        {
            return position_y;
        }

        printf("Ivalid input for Y axis!\n");     
    }
}

char* get_name(void)
{   
    char* name = NULL;

    while(true)
    {
        printf("Enter name for the node: ");
        scanf("%s", name);

        if(strlen(name) < 20)
        {
            return name;
        }

        printf("Ivalid input for name!\n"); 
    }  
}

// Function that inserts a node into the graph
// The function takes five arguments:
int add_edge(struct Graph* graph, int cost, int position_x, int position_y, char name[])
{
    // Validation to add only under the main diagonal and
    // assigning the name and cost of the node in the graph
    if(position_x >= position_y)
    {
        graph->adj[position_x][position_y].cost = cost;
        graph->adj[position_x][position_y].name= name;
    }
    else
    {
        graph->adj[position_y][position_x].cost = cost;
        graph->adj[position_y][position_x].name = name;
    }

    return cost;
}

// Function that creates a dynamic adjacency matrix
// The function takes one argument:
// 1. The size of the matrix int vertices
struct Graph* dynamic_graph_creation(int vertices)
{
    int i, j, temp_x, temp_y;

    // Allocate memory for the graph structure
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));  
    graph->ver = vertices; // Assign the number of vertices in the structure

    // Allocate memory for the adjacency matrix
    graph->adj = (struct Node**)malloc(sizeof(struct Node*) * (size_t)vertices);
    
    for(i = 0; i < vertices; i++) 
    {
        graph->adj[i] = (struct Node*)malloc(sizeof(struct Node) * (size_t)(i + 1));
    }

    // Initialize the adjacency matrix with 0 and NULL
    for(i = 0; i < vertices; i++) 
    {
        for(j = i; j < vertices; j++) 
        {
            graph->adj[i][j].cost = 0;
        }
        
        graph->adj[i][j].name = NULL;
    }

    i = 0;

    do
    {
        temp_x = get_pos_x(vertices);
        temp_y = get_pos_y(vertices);

        add_edge(graph, get_cost(), temp_x, temp_y, get_name());
            
        i++;
    } while(i < vertices);

    return graph;   // Return the initialized graph
}

// Function to free the allocated memory preventing memory leak
// The function takes one argument:
// 1. The already initialized graph (struct Graph* graph)
void free_memory(struct Graph* graph)
{
    for(int i = 0; i < graph->ver; i++) 
    {
        free(graph->adj[i]->name);
    }

    free(graph->adj);
    free(graph);
}
