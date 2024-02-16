#include "maze.h"

#define N_ROWS 5
#define N_COLS 4

int main() {

    int i, k;

    Maze *maze;

    maze = maze_new (N_ROWS, N_COLS);

    if (!maze) {

        maze_free (maze);
        return -1;
    }

    /*Inicialización paredes y espacios*/

    for (i=0; i<N_ROWS; i++) {
        if(maze_setSymbol(maze, i, 0, WALL)==ERROR) {
            return -1;
        }
    }

    for (i=1; i<N_COLS; i++) {
        maze_setSymbol(maze, 0, i, WALL);
    }

    for (i=1; i<N_COLS; i++) {
        maze_setSymbol(maze, N_ROWS - 1, i, WALL);
    }

    for (i=1; i<N_ROWS - 1; i++) {
        maze_setSymbol(maze, i, N_COLS - 1, WALL);
    }

    for (i=1; i<N_COLS - 2; i++) {
        maze_setSymbol(maze, i, N_COLS - 3, SPACE);
    }

    for (i=1; i<N_COLS - 2; i++) {
        maze_setSymbol(maze, i, N_COLS - 2, SPACE);
    }

    /*Inicializacion entrada y salida*/ 

    if (maze_setIn(maze, 0, 2)==ERROR) {
        return -1;
    }

    if (maze_setOut(maze, 3, 3)==ERROR) {
        return -1;
    }

    /*Imprimir puntos*/

    maze_printPoints(stdout, maze);











}