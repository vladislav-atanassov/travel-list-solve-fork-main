#include <stdio.h>
#include <conio.h>

#include "accept_arrow_input.h"
#include "print_solution.h" 
#include "dynamic_graph_creation.h"

// Getting the size of the adjacency matrix
int get_vertices(void)
{
    int vertices;
    
    while(1)
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

// Function to accept the input for a starting point
// through using the left and right arrow on the keyboard
// It always starts from the first point ('A') and by pressing the arrows
// it goes to the next one. If it has come to the end pressed right arrow at the
// last point and goes at the first and if pressed left at the first it goes to the last.
// The function takes two arguments:
// 1. The already declarated
// NOTE: THE FUNCTION RESPONDS ONLY TO THE FUNCTIONAL KEYS ('<-', '->', 'ENTER').
int accept_arrow_input(struct Graph* graph, int vertices)
{
    int point;
    int i = 0;

    printf("Choose starting point.\n");

    printf("Your current choice is point %s.\n", searching_name(graph, i));

    vertices--; // Preventing last element not existing and returning INT_MAX distance

    while(1) 
    {  
        point = getch();
        
        if(point == SPECIAL_ARROW_KEY || point == SPECIAL_KEY_IF_STANETEMT) // Validating that it is a special symbol
        {
            point = getch();
            
            if(point == RIGHT_ARROW_KEY)        // Catching right arrow character
            {
                i++;

                if(i > vertices)
                {
                    i -= vertices;              // Go to the beginning if the choice becomes unavailable
                }
                
                printf("Your current choice is point %s.\n", searching_name(graph, i));
            }
            else if(point == LEFT_ARROW_KEY)    // Catching left arrow charecter
            { 
                i--;

                if(i < 0)
                {
                    i += vertices;              // Go to the end if the choice becomes unavailable
                }

                printf("Your current choice is point %s.\n", searching_name(graph, i));
            }
        }
        else if(point == ENTER_KEY)             // Catching ENTER character
        {
            printf("\nYou chose point '%s'.\n\n", searching_name(graph, i)); 
            
            return i;                           // Return the gotten result
        }
    }
}
