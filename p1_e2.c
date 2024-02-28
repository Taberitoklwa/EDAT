#include "maze.h"

#define N_ROWS 5
#define N_COLS 4

int main() {

    int i;

    direction dir;

    Point *output;

    Maze *maze;

    maze = maze_new (N_ROWS, N_COLS);

    if (!maze) {

        maze_free (maze);
        return ERROR;
    }

    /*Inicialización paredes y espacios*/


    for (i=0; i<N_ROWS; i++) {
        if(maze_setSymbol(maze, i, 0, WALL)==ERROR) {
            maze_free (maze);
            return ERROR;
        }
    }

    for (i=1; i<N_COLS; i++) {
        if(maze_setSymbol(maze, 0, i, WALL)==ERROR) {
            maze_free (maze);
            return ERROR;
        }
    }

    for (i=1; i<N_COLS; i++) {
        if(maze_setSymbol(maze, N_ROWS - 1, i, WALL)==ERROR) {
            maze_free (maze);
            return ERROR;
        }
    }

    for (i=1; i<N_ROWS - 1; i++) {
        if(maze_setSymbol(maze, i, N_COLS - 1, WALL)==ERROR) {
            maze_free (maze);
            return ERROR;
        }
    }

    /*Entrada*/

    if(maze_setSymbol(maze, 0, 2, IN)==ERROR){
        maze_free (maze);
        return ERROR;
    }

    /*Salida*/

    if(maze_setSymbol(maze, 3, 3, OUT)==ERROR){
        maze_free (maze);
        return ERROR;
    }

    /*Inicializacion entrada y salida*/ 

    if (maze_setIn(maze, 0, 2)==ERROR) {
        maze_free (maze);
        return ERROR;
    }

    if (maze_setOut(maze, 3, 3)==ERROR) {
        maze_free (maze);
        return ERROR;
    }
    

    output = maze_getOut(maze);

    if (output == NULL) {
        maze_free (maze);
        return ERROR;
    }


    /*Imprimir puntos*/

    if(maze_printPoints(stdout, maze)==ERROR){
        maze_free (maze);
        return ERROR;
    }

    /*Imprimir laberinto*/

    if(maze_print(stdout, maze)==ERROR) {
        maze_free (maze);
        return ERROR;
    }

    /*vecinos de la salida*/

    fprintf(stdout,"Get output neighbors:\n");

    for(dir=0; dir<=STAY; dir++){
        (point_print(stdout, (void*)maze_getNeighbor(maze, output, dir)));
    }


    maze_free(maze);

    return OK;
}
