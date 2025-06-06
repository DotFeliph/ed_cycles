#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "graph.h"

#define MAX_FILENAME 50;

FILE * openFile(char const *filename);

int main(int argc, char const *argv[])
{
    FILE *file = NULL;
    Graph graph = NULL;
    // TODO: give examples files, ang give options to the user to choose
    switch (argc)
    {
    case 1:
        printf("Program usagem: ./main [FILENAME] \n");
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