
#include "maze.h"

#define NPOINTS 4


int main()
{

    int i = 0;

    Point *point[NPOINTS];

    for(i=0; i<NPOINTS; i++){
        point[i]=NULL;
    }

    point[0] = point_new(0, 0, WALL);

    point[1] = point_new(0, 1, WALL);

    point_print(stdout, point[0]);

    point_print(stdout, point[1]);

    fprintf(stdout, "\n¿Equal points p[0] and p[1]?");

    if (point_equal(point[0], point[1]) == true)
    {

        fprintf(stdout, "Yes");
    }
    else
    {

        fprintf(stdout, "No");
    }

    fprintf(stdout, "\nCreating p[2]:");

    point[2]=point_hardcpy(point[0]);

    point_print(stdout, point[2]);

    fprintf(stdout, "\n¿Equal points p[0] and p[2]?");

    if (point_equal(point[0], point[2]) == true)
    {

        fprintf(stdout, "Yes");
    }
    else
    {

        fprintf(stdout, "No");
    }

    fprintf(stdout, "\nModifying p[2]:");

    point_setSymbol(point[2], SPACE);

    point_print(stdout, point[2]);


    fprintf(stdout, "\n¿Equal points p[0] and p[2]?");

    if (point_equal(point[0], point[2]) == true)
    {

        fprintf(stdout, "Yes ");
    }
    else
    {

        fprintf(stdout, "No");
    }

    fprintf(stdout, "\nAssign p[3] = p[0]");

    point[3] = point[0];

    fprintf(stdout, "\nModifying p[3]:");

    point_setSymbol(point[3], OUT);

    point_print(stdout, point[3]);

    fprintf(stdout, "\n");

    for (i = 0; i < NPOINTS; i++)
    {
        point_print(stdout, point[i]);
    }

    for (i = 0; i < 3; i++)
    {
        if (point[i]){
            free(point[i]);
        }
    }

    return 0;
}
