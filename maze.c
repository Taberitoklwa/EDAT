
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

struct _Point { /*defines the point struct*/ 
   int x, y;
   char symbol;
   bool visited; /*for DFS*/
};

/*Function implementation*/

Point *point_new(int x, int y, char symbol) {

   Point *point=NULL;

   point = (Point*)calloc(1, sizeof(Point));

   if (point==NULL || x<0 || y<0) {
       return NULL;
   }

   if (symbol!=IN && symbol!=OUT && symbol!=BARRIER && symbol!=SPACE) {
       return NULL;
   }

   point->x = x;
   point->y = y;
   point->symbol = symbol;

   return point;

}

void point_free(Point *p) {

   free(p);

}

int point_getX(const Point *p) {

   if(!p) {
       return INT_MAX;
   }

   return p->x;

}

int point_getY(const Point *p){

   if(!p) {
       return INT_MAX;
   }

   return p->y;

}

char point_getSymbol(const Point *p){

   if(!p) {
       return ERRORCHAR;
   }

   return p->symbol;

}

Status point_setX(Point *p, int x) {

   if(!p || x<0) {
       return ERROR;
   }

   p->x = x;

   return OK;
}

Status point_setY(Point *p, int y) {

       if(!p || y<0) {
       return ERROR;
   }

   p->y = y;

   return OK;
}

Status point_setSymbol(Point *p, char c) {

   if(!p) {
       return ERROR;
   }

   /*Cambiado error devolvia puntero a NULL--*/

   if (c!=IN && c!=OUT && c!=BARRIER && c!=SPACE) {
       return ERROR;
   }

   p->symbol = c;

   return OK;
}

bool point_getVisited(const Point *p) {

   if(!p) {
       return false;
   }

   return p->visited;

}   

Status point_setVisited(Point *p, bool bol) {

   if(!p) {
       return ERROR;
   }

   p->visited = bol;

   return OK;
} 


Point *point_hardcpy(const Point *src) {

   Point *point=NULL;

   point = point_new(src->x, src->y, src->symbol);

   return point;

}

bool point_equal(const void *p1, const void *p2) {

   Point *p11=NULL, *p22=NULL;

   if (!p1 || !p2) {
       return false;
   }

   p11 = (Point*)p1;
   p11 = (Point*)p1;

   if (point_getX(p11)!= point_getX(p22) || point_getY(p11) != point_getY(p22) || point_getSymbol(p11) != point_getSymbol(p22)) {
       return false;
   }

   return true;

}

int point_print(FILE *pf, const void *p) {

   Point *pp=NULL;
   int ret;
   
   if(!p || !pf) {
       return -1;
   }

   pp = (Point*)p;

   ret = fprintf(stdout, "[(%d, %d): %c]", point_getX(pp), point_getY(pp), point_getSymbol(pp));

   return ret;

}