#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "graph.h"
#include <stdbool.h>

FILE * openFile(char const *filename);

int main(int argc, char const *argv[])
{
    FILE *file = NULL;
    Graph graph = NULL;

    switch (argc)
    {
    case 1:
        printf("Program usage: main [file]\n");
        return 1;
        break;

    case 2: 

        if((file = openFile(argv[1]) ) == NULL)
        {
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


FILE * openFile(char const *filename){

    FILE *file = fopen(filename, "r");

    if(file == NULL){
        printf("Error opening the file: %s\n", strerror(errno) );
        return NULL;
    } 
    return file;
}