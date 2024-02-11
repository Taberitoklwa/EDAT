
/**
 * @brief it defines the functions and structures of maze
 *
 * @file maze.c
 * @version 1
 * @authors Álvaro Leonardo & Diego Tabero
 */

#include "maze.h"
#include "types.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*Mirar ansi*/

struct _Point
{ /*defines the point struct*/
    int x, y;
    char symbol;
    bool visited; /*for DFS*/
};

struct _Maze
{
    int ncols, nrows;
    Point *in, *out;
    Point **map;
};

/*Function implementation*/

Point *point_new(int x, int y, char symbol)
{

    Point *point = NULL;

    point = (Point *)calloc(1, sizeof(Point));

    if (point == NULL || x < 0 || y < 0)
    {
        return NULL;
    }

    if (symbol != IN && symbol != OUT && symbol != BARRIER && symbol != SPACE)
    {
        return NULL;
    }

    point->x = x;
    point->y = y;
    point->symbol = symbol;

    return point;
}

void point_free(Point *p)
{

    free(p);
}

int point_getX(const Point *p)
{

    if (!p)
    {
        return INT_MAX;
    }

    return p->x;
}

int point_getY(const Point *p)
{

    if (!p)
    {
        return INT_MAX;
    }

    return p->y;
}

char point_getSymbol(const Point *p)
{

    if (!p)
    {
        return ERRORCHAR;
    }

    return p->symbol;
}

Status point_setX(Point *p, int x)
{

    if (!p || x < 0)
    {
        return ERROR;
    }

    p->x = x;

    return OK;
}

Status point_setY(Point *p, int y)
{

    if (!p || y < 0)
    {
        return ERROR;
    }

    p->y = y;

    return OK;
}

Status point_setSymbol(Point *p, char c)
{

    if (!p)
    {
        return ERROR;
    }

    /*Cambiado error devolvia puntero a NULL--*/

    if (c != IN && c != OUT && c != BARRIER && c != SPACE)
    {
        return ERROR;
    }

    p->symbol = c;

    return OK;
}

bool point_getVisited(const Point *p)
{

    if (!p)
    {
        return false;
    }

    return p->visited;
}

Status point_setVisited(Point *p, bool bol)
{

    if (!p)
    {
        return ERROR;
    }

    p->visited = bol;

    return OK;
}

Point *point_hardcpy(const Point *src)
{

    Point *point = NULL;

    point = point_new(src->x, src->y, src->symbol);

    return point;
}

bool point_equal(const void *p1, const void *p2)
{

    Point *p11 = NULL, *p22 = NULL;

    if (!p1 || !p2)
    {
        return false;
    }

    p11 = (Point *)p1;
    p11 = (Point *)p1;

    if (point_getX(p11) != point_getX(p22) || point_getY(p11) != point_getY(p22) || point_getSymbol(p11) != point_getSymbol(p22))
    {
        return false;
    }

    return true;
}

int point_print(FILE *pf, const void *p)
{

    Point *pp = NULL;
    int ret;

    if (!p || !pf)
    {
        return -1;
    }

    pp = (Point *)p;

    ret = fprintf(pf, "[(%d, %d): %c]", point_getX(pp), point_getY(pp), point_getSymbol(pp));

    return ret;
}

/**
 * @brief  Creates a new empty Maze with nrows and ncols.
 *
 * Allocates memory for a new map and initializes it to be empty
 * (no points).
 *
 * @param nrows, ncols Dimension of the map
 *
 * @return A pointer to the graph if it was correctly allocated,
 * NULL otherwise.
 **/

Maze *maze_new(int nrows, int ncols)
{

    Maze *maze = NULL;

    Point p;

    int i = 0, j = 0;

    maze = (Maze *)calloc(1, sizeof(Maze));

    maze->nrows = nrows;
    maze->ncols = ncols;
    maze->in = &p;
    maze->out = &p;

    if (!maze)
    {
        return NULL;
    }

    maze->map = (Point **)calloc(nrows, sizeof(Point *));

    if (!maze->map)
    {
        maze_free(maze);
        return NULL;
    }

    for (i = 0; i < nrows; i++)
    {
        maze->map[i] = (Point *)calloc(ncols, sizeof(Point));
        if(!maze->map[i]){
            maze_free(maze);
            return NULL;
        }
    }

    for (i = 0; i < nrows; i++)
    {
        for (j = 0; j < ncols; j++)
        {
            maze->map[i][j] = p;
        }
    }

    return maze;
}

/**
 * @brief Frees a maze.
 *
 * Frees all the memory allocated for the maze
 *
 * @param g Pointer to graph to be freed.
 **/

void maze_free(Maze *maze)
{

    int i, j;

    for (i = 0; i < maze->nrows; i++)
    {
        for (j = 0; j < maze->ncols; j++)
        {
            if (maze->map[i])
            {
                free(maze->map[i]);
            }
        }
    }

    if (maze->map)
    {

        free(maze->map);
    }

    if (maze)
    {
        free(maze);
    }
}

Status maze_setSymbol(const Maze *maze, int x, int y, char sym){

    if (!maze)
    {
        return ERROR;
    }

    

    if (sym != IN && sym != OUT && sym != BARRIER && sym != SPACE)
    {
        return ERROR;
    }

    point_setSymbol(&maze->map[x][y], sym);

    return OK;

}

Status maze_setVisited(const Maze *maze, int x, int y, bool visited){

    if (!maze)
    {
        return ERROR;
    }

    point_setVisited(&maze->map[x][y], visited);

    return OK;

}

Point *maze_getPoint(const Maze *maze, int x, int y){

    Point *point;

    point=&maze->map[x][y];

    return point;
}

char maze_getSymbol(const Maze *maze, int x, int y){

    Point *point;

    char sym;

    point=maze_getPoint(maze, x, y);

    sym=point->symbol;

    return sym;

}

bool maze_isVisited(const Maze *maze, int x, int y){

    Point *point;

    point=maze_getPoint(maze,x,y);

    point_setVisited(point, point->visited);



}

Status maze_setIn(Maze *maze, int x, int y){

    char sym=maze_getSymbol(maze, x, y);

    maze->in=point_new(x,y,sym);
    maze->out=point_new(x,y,sym);


}




Status maze_setOut(Maze *maze, int x, int y){

    char sym=maze_getSymbol(maze, x, y);

    maze->in=point_new(x,y,sym);
    maze->out=point_new(x,y,sym);

}

/* check whether coordinates are valid for maze */
Status maze_checkCoordinates(const Maze *maze, int x, int y){

    if(x>maze->nrows || y>maze->ncols || x<0 || y<0 ){
        return ERROR;
    }

    return OK;

}

int maze_getNrows(const Maze *maze){

return maze->nrows;

}

int maze_getNcols(const Maze *maze){

return maze->ncols;

}

int maze_printPoints(FILE *fp, const Maze *maze){

Point *point;

int x,y, ret=0;


for(x=0; x<maze->nrows; x++){
    for(y=0 ; y<maze->ncols; y++, ret++){
        point=maze_getPoint(maze->map,x,y); 
        if(point_print(stdout,  point)<0)
        {

            return -1;

        }


    }

}
    return ret;

}

/* START [maze_print] */
/**
 * @brief Prints a maze in .
 *
 */

int maze_print(FILE *fp, const Maze *maze);

/* START [maze_readFromFile] */
/**
 * @brief Reads a map definition from a text file.
 *
 * Reads a maze description from the text file filename and returns the maze,
 * This function allocates memory for the maze
 *
 * The file contains a header with the map number of rows and cols.
 * The next file lines corresponds with the points of the map.
 *.
 * For example the file:
 *
 * 3 4
 * ++++
 * +io+
 * ++++
 *
 * Represents a map with 3 rows, 4 columns and the points:
 * [(0, 0): +][(0, 1): +][(0, 2): +][(0, 3): +][(1, 0): +][(1, 1): i]
 * [(1, 2): o][(1, 3): +][(2, 0): +][(2, 1): +][(2, 2): +][(2, 3): +]
 *
 * @param filename, name of text file
 *
 * @return the newly allocated maze or NULL if there is any error
 */
Maze *maze_readFromFile(const char *filename);
