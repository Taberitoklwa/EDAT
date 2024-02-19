
#include "maze.h"

#define NPOINTS 4

int main()
{

    int i = 0;

    Point *point[NPOINTS];

    for(i=0; i<NPOINTS; i++){
        point[i]=NULL;
    }

    /*The free loop checks if the pointer points to NULL, and if not, frees the reserved memory*/

    if(!(point[0] = point_new(0, 0, WALL))){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS; i++){
            point_free(point[i]);
        }
        return ERROR;
    }
    

    if(!(point[1] = point_new(0, 1, WALL))){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS; i++){
            point_free(point[i]);
        }
        return ERROR;
    }

    if(point_print(stdout, point[0])<0){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS; i++){
            point_free(point[i]);
        }
        return ERROR;
    }

    if(point_print(stdout, point[1])<0){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS; i++){
            point_free(point[i]);
        }
        return ERROR;
    }

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

    if(!(point[2]=point_hardcpy(point[0]))){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS; i++){
            point_free(point[i]);
        }
        return ERROR;
    }

    if(point_print(stdout, point[2])<0){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS; i++){
            point_free(point[i]);
        }
        return ERROR;
    }

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

    if(!(point_setSymbol(point[2], SPACE))){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS; i++){
            point_free(point[i]);
        }
        return ERROR;
    }

    if(point_print(stdout, point[2])<0){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS; i++){
            point_free(point[i]);
        }
        return ERROR;
    }


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

    /*The free loop iterates to position Npoint-1 since we have already freed point[0] and we don't have to free point[3] because point[3] is assigned to point[0].*/

    if(!point_setSymbol(point[3], OUT)){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS-1; i++){
            point_free(point[i]);
        }
        return ERROR;
    }

    if(point_print(stdout, point[3])<0){
        fprintf(stdout, "ERROR\n");
        for(i=0; i<NPOINTS-1; i++){
            point_free(point[i]);

        }
        return ERROR;
    }

    fprintf(stdout, "\n");

    for(i=0; i<NPOINTS; i++){
        if(point_print(stdout, point[i])<0){
            fprintf(stdout, "ERROR\n");
            for(i=0; i<NPOINTS-1; i++){
                point_free(point[i]);
            }
            return ERROR;
        }
    }    

    fprintf(stdout, "\n");

    for (i = 0; i < NPOINTS-1; i++)
    {
        point_free(point[i]);
    }

    return OK;
}
