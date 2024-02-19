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

   if (symbol != IN && symbol != OUT && symbol != WALL && symbol != SPACE)
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
    if(p){
        free(p);
    }
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

   if (c != IN && c != OUT && c != WALL && c != SPACE)
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
   p22 = (Point *)p2;

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

   if(nrows<0 || ncols<0){
       return NULL;
   }

   Maze *maze = NULL;

   int i = 0, j = 0;

   maze = (Maze *)calloc(1, sizeof(Maze));

   maze->nrows = nrows;
   maze->ncols = ncols;
   maze->in = NULL;
   maze->out = NULL;

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

           point_setX(&maze->map[i][j],i);
           point_setY(&maze->map[i][j],j);
           maze_setSymbol(maze,i,j, SPACE);
           maze_setVisited(maze,i,j,false);
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

   int i;

   if(maze->in){
       free(maze->in);
       maze->in=NULL;
   }

   if(maze->out){
       free(maze->out);
       maze->out=NULL;
   }

   for (i = 0; i < maze->nrows; i++)
   {
        if (maze->map[i])
        {
            free(maze->map[i]);
            maze->map[i]=NULL;
        }
       
   }

   if (maze->map)
   {
       free(maze->map);
       maze->map=NULL;
   }

   if (maze)
   {
       free(maze);
       maze=NULL;
   }
}

Status maze_setSymbol(const Maze *maze, int x, int y, char sym){

   if (!maze)
   {
       return ERROR;
   }

   

   if (sym != IN && sym != OUT && sym != WALL && sym != SPACE)
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

   if(!maze){
       return NULL;
   }

   Point *point=&maze->map[x][y];

   return point;
}

char maze_getSymbol(const Maze *maze, int x, int y){

   if(!maze){
       return '\0';    
   }

   Point *point;

   point=maze_getPoint(maze, x, y);

   return point->symbol;;

}



bool maze_isVisited(const Maze *maze, int x, int y){

   if(!maze){
       return false;
   }

   Point *point;

   point=maze_getPoint(maze,x,y);

   return point_getVisited(point);

}

Status maze_setIn(Maze *maze, int x, int y){

   if(!maze){
       return ERROR;
   }

   maze->in=point_new(x,y,IN);

   return OK;


}


Status maze_setOut(Maze *maze, int x, int y){

    if(!maze){
       return ERROR;
   }

   maze->out=point_new(x,y,OUT);

   return OK;

}

Point *maze_getIn(const Maze *maze){
    if(!maze){
        return NULL;
    }

    return maze->in;
}
Point *maze_getOut(const Maze *maze){
    if(!maze){
        return NULL;
    }

    return maze->out;
}

Point *maze_getNeighbor(const Maze *maze, const Point *p, direction dir){

   Point *point=NULL;

   if (!maze || !p) {
       return NULL;
   }

   if (dir == STAY) {
       return NULL;
   }

   if (dir == RIGHT) {

       if(!maze_checkCoordinates(maze, p->x, p->y+1)){

        return NULL;

       }

       point = maze_getPoint(maze, p->x, p->y+1);

       if (!(point)) {
           return NULL;
       }

       return point;
   }

   if (dir == UP) {

    if(!maze_checkCoordinates(maze, p->x-1, p->y)){

        return NULL;

    }

       point = maze_getPoint(maze, p->x-1, p->y);

       if (!(point)) {
           return NULL;
       }

       return point;
   }

   if (dir == LEFT) {

        if(!maze_checkCoordinates(maze, p->x, p->y-1)){

        return NULL;

    }   
       
       point = maze_getPoint(maze, p->x, p->y-1);

       if (!(point)) {
           return NULL;
       }

       return point;
   }

   if (dir == DOWN) {

    if(!maze_checkCoordinates(maze, p->x+1, p->y)){

        return NULL;

    }
       
       point = maze_getPoint(maze, p->x+1, p->y);

       if (!(point)) {
           return NULL;
       }

       return point;
   }

   return NULL;
 
}

/* check whether coordinates are valid for maze */
Status maze_checkCoordinates(const Maze *maze, int x, int y){

   if(x>=maze->nrows || y>=maze->ncols || x<0 || y<0 ){
       return ERROR;
   }

   return OK;

}

//Mirar control errores


int maze_getNrows(const Maze *maze){return maze->nrows;}

int maze_getNcols(const Maze *maze){return maze->ncols;}

int maze_printPoints(FILE *fp, const Maze *maze){

Point *point;

int x,y, ret=0;

fprintf(fp, "Maze points: %d rows %d cols\n", maze->nrows, maze->ncols);

for(x=0; x<maze->nrows; x++){
   for(y=0 ; y<maze->ncols; y++, ret++){
       point=maze_getPoint(maze,x,y); 
       if(point_print(stdout,  (void *)point)<0)
       {

           return ERROR;

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

int maze_print(FILE *fp, const Maze *maze) {

   if(!maze){
       return ERROR;
   }

int x, y, ret;
char sym;

fprintf(fp, "\nMaze : %d rows %d cols\n", maze->nrows, maze->ncols);

if(point_print(fp, maze->in)<0){
    return ERROR;
}
if(point_print(fp, maze->out)<0){
    return ERROR;
}

fprintf(fp, "\n");

for(x=0; x<maze->nrows; x++){
   for(y=0 ,ret=0; y<maze->ncols; y++, ret++){
       if(!(sym=maze_getSymbol(maze,x,y))){
            return ERROR;
       }
       fprintf(fp, "%c", sym);
   }
   fprintf(fp, "\n");

}



   return ret;


}

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
Maze *maze_readFromFile(const char *filename){

    int rows, cols, i, j;

    char sym;

    Maze *maze;

    FILE * fmaze;



    if(filename==NULL){
        return NULL;
    }

    fmaze=fopen(filename, "r");

    if(fmaze==NULL){
        return NULL;
    }

    fscanf(fmaze, "%d %d", &rows, &cols);

    if(!(maze=maze_new(rows, cols))){
        return NULL;
    }

    for (i = 0; i < rows; i++)
   {
       for (j = 0; j < cols; j++)
       {
        fscanf(fmaze, "%c", &sym);
        if(sym=='\n'){
            fscanf(fmaze, "%c", &sym);
        }

        if(sym==IN){
            maze_setIn(maze, i, j);
        }

        if(sym==OUT){
            maze_setOut(maze, i, j);
        }

        maze_setSymbol(maze, i, j, sym);
       }
   }

    fclose(fmaze);

    return maze;

}

