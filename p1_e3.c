#include "maze.h"

/// @brief 
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char *argv[]) {

    Maze *maze;

    Point *aux;

    direction dir;

    fprintf(stdout, "Reading maze from %s", argv[1]);

    maze=maze_readFromFile(argv[1]);

    maze_print(stdout, maze);

    aux=maze_getOut(maze);

    fprintf(stdout, "\nGet neighbors of output point ");

    point_print(stdout, aux);

    fprintf(stdout,"\n");

    for(dir=0; dir<=4; dir++){
        point_print(stdout, maze_getNeighbor(maze, aux, dir));
    }

    //The point in the lower right corner is the one corresponding to the coordinates Nrows-1 Ncols-1 of the array

    aux=maze_getPoint(maze, maze_getNrows(maze)-1, maze_getNcols(maze)-1);

    fprintf(stdout, "\nGet neighbors of bottom right corner");

    point_print(stdout, aux);

    fprintf(stdout,"\n");

    for(dir=0; dir<=4; dir++){
        point_print(stdout, maze_getNeighbor(maze, aux, dir));
    }

    maze_free(maze);

    return 0;
}