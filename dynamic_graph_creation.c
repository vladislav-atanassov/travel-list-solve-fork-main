#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dynamic_graph_creation.h"

// Getting the size of the adjacency matrix
int get_vertices(void)
{
    int vertices;
    
    while(true)
    {
        printf("Enter number of nodes: ");
        scanf("%d", &vertices);

        // Checking if the matrix is valid or not
        // 1x1 matrix is not valid and negative size is not valid too
        
        if(vertices > 1)    
        {
            return vertices;
        }
        
        printf("Invalid input!\n");
    }
}

// Function to get the cost of the node
// The funtion takes not arguments
int get_cost(void)
{
    int cost;

    while(true)
    {
        printf("Enter cost for the node: ");
        if (scanf("%d", &cost) != 1) {
            printf("Invalid input for cost!\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if(cost > 0) // Validating the cost of the node
        {
            while (getchar() != '\n'); // Clear input buffer
            return cost;
        }

        printf("Invalid input for cost!\n");
        while (getchar() != '\n'); // Clear input buffer
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
        if(position_x >= 0 && (position_x < vertices)) 
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

    while(true)
    {
        printf("Enter position for the edge on the Y axis: ");
        scanf("%d", &position_y);
        
        // Validating out of bounds error
        if(position_y >= 0 && (position_y < vertices))
        {
            return position_y;
        }

        printf("Ivalid input for Y axis!\n");     
    }
}

char* get_name(void) {
    char* name = (char *)malloc(sizeof(char) * MAX_NAME_SIZE); // Adjust the size as needed
    
    while(true) {
        printf("Enter name for the node: ");
        fgets(name, MAX_NAME_SIZE, stdin); // Read the string safely using fgets

        // Remove the newline character if present
        size_t len = strlen(name);
        if (name[len - 1] == '\n') {
            name[len - 1] = '\0';
        }

        if (strlen(name) > 0) {
            return name;
        }

        printf("Invalid input for name!\n");
    }
}



// Function that inserts a node into the graph
// The function takes five arguments:
void add_edge(struct Graph* graph, int position_x, int position_y, char* name, int cost)
{
    // Validation to add only under the main diagonal and
    // assigning the name and cost of the node in the graph
    if(position_x <= position_y)
    {
        graph->adj[position_x][position_y].cost = cost;
        graph->adj[position_x][position_y].name= name;
    }
    else
    {
        graph->adj[position_y][position_x].cost = cost;
        graph->adj[position_y][position_x].name = name;
    }
}

// Function that creates a dynamic adjacency matrix
// The function takes one argument:
// 1. The size of the matrix int vertices
struct Graph* dynamic_graph_creation(int vertices) {
    int i = 0;

    // Allocate memory for the graph structure
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));  
    graph->ver = vertices; // Assign the number of vertices in the structure

    // Allocate memory for the adjacency matrix
    graph->adj = (struct Node**)malloc(sizeof(struct Node*) * (size_t)vertices);
    
    for(i = 0; i < vertices; i++) 
    {
        graph->adj[i] = (struct Node*)malloc(sizeof(struct Node) * (size_t)vertices);
    }

    // Initialize the adjacency matrix with 0 and NULL
    for(i = 0; i < vertices; i++)
    {
        for(int j = 0; j < vertices; j++) 
        {
            graph->adj[i][j].cost = 0;
            graph->adj[i][j].name = NULL;
        }
    }

    for(i = 0; i < vertices; i++) 
    {
        add_edge(graph, get_pos_x(vertices), get_pos_y(vertices), get_name(), get_cost());
    }

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
