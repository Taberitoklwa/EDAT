#include "maze.h"

int main(int argc, char *argv[]) {

    Maze *maze;

    Point *aux;

    direction dir;

    //If the user did not enter any file during the execution of the program, it finish

    if(!argv[1]){
        return ERROR;
    }

    fprintf(stdout, "Reading maze from %s", argv[1]);

    if(!(maze=maze_readFromFile(argv[1]))){
        return ERROR;
    }

    if(maze_print(stdout, maze)==ERROR){
        maze_free (maze);
        return ERROR;
    }

    aux=maze_getOut(maze);

    if (aux == NULL) {
        maze_free (maze);
        return ERROR;
    }

    fprintf(stdout, "\nGet neighbors of output point ");

    if(point_print(stdout, aux)<0){
        maze_free (maze);
        return ERROR;
    }

    fprintf(stdout,"\n");

    for(dir=0; dir<=STAY; dir++){
        (point_print(stdout, (void*)maze_getNeighbor(maze, aux, dir)));
    }

    //The point in the lower right corner is the one corresponding to the coordinates Nrows-1 Ncols-1 of the array

    aux=maze_getPoint(maze, maze_getNrows(maze)-1, maze_getNcols(maze)-1);

    if (aux == NULL) {
        maze_free (maze);
        return ERROR;
    }

    fprintf(stdout, "\nGet neighbors of bottom right corner");

    if(point_print(stdout, aux)<0){
        maze_free (maze);
        return ERROR;
    }

    fprintf(stdout,"\n");

    for(dir=0; dir<=STAY; dir++){
        (point_print(stdout, (void*)maze_getNeighbor(maze, aux, dir)));
    }

    maze_free(maze);

    return OK;
}