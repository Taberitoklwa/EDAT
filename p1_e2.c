#include "maze.h"

#define N_ROWS 5
#define N_COLS 4

int main() {

    int i;

    Point *output, *aux;

    Maze *maze;

    maze = maze_new (N_ROWS, N_COLS);

    if (!maze) {

        maze_free (maze);
        return ERROR;
    }

    /*Inicialización paredes y espacios*/


    for (i=0; i<N_ROWS; i++) {
        if(maze_setSymbol(maze, i, 0, WALL)==ERROR) {
            return ERROR;
        }
    }

    for (i=1; i<N_COLS; i++) {
        if(maze_setSymbol(maze, 0, i, WALL)==ERROR) {
            return ERROR;
        }
    }

    for (i=1; i<N_COLS; i++) {
        if(maze_setSymbol(maze, N_ROWS - 1, i, WALL)==ERROR) {
            return ERROR;
        }
    }

    for (i=1; i<N_ROWS - 1; i++) {
        if(maze_setSymbol(maze, i, N_COLS - 1, WALL)==ERROR) {
            return ERROR;
        }
    }

    /*Entrada*/

    if(maze_setSymbol(maze, 0, 2, IN)==ERROR){
        return ERROR;
    }

    /*Salida*/

    if(maze_setSymbol(maze, 3, 3, OUT)==ERROR){
        return ERROR;
    }

    /*Inicializacion entrada y salida*/ 

    if (maze_setIn(maze, 0, 2)==ERROR) {
        return ERROR;
    }

    if (maze_setOut(maze, 3, 3)==ERROR) {
        return ERROR;
    }
    

    output = maze_getOut(maze);

    if (output == NULL) {
        return ERROR;
    }


    /*Imprimir puntos*/

    if(maze_printPoints(stdout, maze)==-1){
        return ERROR;
    }

    /*Imprimir laberinto*/

    if(maze_print(stdout, maze)==-1) {
        return ERROR;
    }

    /*vecinos de la salida*/

    fprintf(stdout,"Get output neighbors:\n");

    aux = maze_getNeighbor(maze, output, UP);

    point_print(stdout, aux);
    
    aux = maze_getNeighbor(maze, output, RIGHT);

        point_print(stdout, aux);

    aux = maze_getNeighbor(maze, output, LEFT);

        point_print(stdout, aux);

    aux = maze_getNeighbor(maze, output, DOWN);

        point_print(stdout, aux);


    maze_free(maze);

    return 0;

}