#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_graph_creation.h"

// Function to get the cost of the node
// The funtion takes not arguments
int get_cost(void)
{
    int cost;

    while(1)
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

    while(1)
    {
        printf("Enter position for the edge on the X axis: ");
        scanf("%d", &position_x);

        if(position_x > 0 || position_x < vertices - 1) // Validating out of index error
        {
            return position_x;
        }

        printf("Ivalid input for X axis!\n");      
    }
}

// Function to get the Y axis position of the node
// The function takes one argument
// 1. The size of the matrix int vertices
int get_pos_y(int vertices)
{
    int position_y;

    while(1)
    {
        printf("Enter position for the edge on the Y axis: ");
        scanf("%d", &position_y);

        if(position_y > 0 || position_y < vertices - 1) // Validating out of index error
        {
            return position_y;
        }

        printf("Ivalid input for Y axis!\n");     
    }
}

// Function that inserts a node into the graph
// The function takes five arguments:
int add_edge(struct Graph* graph, int cost, int position_x, int position_y, char name[])
{
    // Assignning the cost of the node in the graph

    graph->adj[position_x][position_y].cost = cost;
    graph->adj[position_y][position_x].cost = cost;

    // Assigning the name of the node in the graph
    
    graph->adj[position_x][position_y].name= name;
    graph->adj[position_y][position_x].name = name;

    return cost;
}

char* get_name(struct Graph* graph, int pos_x, int pos_y)
{   
    char* name = (char*)malloc(sizeof(char) * SIZE_NAME);

    if(name == NULL)
    {
        perror("Error: Memory allocation failed!");
        return NULL;
    }

    while(1)
    {
        printf("Enter name for the node: ");
        scanf("%.20s", name);

        char* temp_name = (char*)realloc(name, sizeof(char) * strlen(name));

        if(temp_name == NULL)
        {
            printf("Error: Memory allocation failed!");
            free(name);
            return NULL;
        }

        name = temp_name;
        
        return name;
    }  
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
    graph->adj = (struct Node**)malloc(sizeof(struct Node*) * vertices);
    
    for (i = 0; i < vertices; i++) 
    {
        graph->adj[i] = (struct Node*)malloc(sizeof(struct Node) * vertices);
    }

    // Initialize the adjacency matrix with NULL
    for (i = 0; i < vertices; i++) 
    {
        for (j = 0; j < vertices; j++) 
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

        add_edge(graph, get_cost(), temp_x, temp_y, get_name(graph, temp_x, temp_y));
            
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

    free(graph);
}
