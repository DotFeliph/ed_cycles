#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "graph.h"
#include <stdbool.h>

// returns true if succeeded
bool openFile(char const *filename[], FILE *file);

int main(int argc, char const *argv[])
{
    FILE *file = NULL;
    Graph graph = NULL;
    switch (argc)
    {
    case 1:
        printf("Program usage: main [file]");
        return 1;
        break;

    case 2: 
        if(openFile(argv[1], file) == false){
            return 1;
        }

        graph = loadGraph(file, graph);
            
        depthFirstSearch(graph);
        fclose(file);
        freeGraph(graph);
        freeVertexMap();
        graph = NULL;
        
        break;
    default:
        printf("Program usage: main [file]");
        return 1;
        break;        
    }
    
    return 0;
}


bool openFile(char const *filename[], FILE *file){
    
    if(file = fopen(filename, "r") == NULL){
        printf("Error opening the file: ", strerror(errno) );
        return false;
    } 
    return true;
}