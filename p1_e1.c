

#include "maze.h"


void freepointers(Point *point[]){

    int i;

    for(i=0; i<3; i++){
        if(point[i])
            free(point[i]); 
    }
}

int main(){

int i=0;


Point *point[4];

for(i=0; i<3; i++){
    point[i]=NULL;
}

point[0] = point_new(0, 0, WALL);

point[1] = point_new(0, 1, WALL);

if(point_print(stdout, point[0])<0){
    freepointers(point);
    return -1;
}

if(point_print(stdout, point[1])<0){
    freepointers(point);
    return -1;
}


fprintf(stdout, "\n¿Equal points p[0] and p[1]?");

if(point_equal(point[0], point[1]) == true){

fprintf(stdout,"NO");

}
else{

fprintf(stdout,"YES");

}


fprintf(stdout, "\nCreating p[2]:");

point[2]=point_hardcpy(point[0]);

if (point_print(stdout, point[2])<0){
    freepointers(point);
    return -1;
}

fprintf(stdout, "\n¿Equal points p[0] and p[2]?");

if(point_equal(point[0], point[2]) == true){

fprintf(stdout,"NO");

}
else{

fprintf(stdout,"YES");

}

fprintf(stdout, "\nModifying p[2]:");

point_setSymbol(point[2], SPACE);

if(point_print(stdout, point[2])<0){
    freepointers(point);
    return -1;
}

fprintf(stdout, "\n¿Equal points p[0] and p[2]?");

if(point_equal(point[0], point[2]) == true){

fprintf(stdout,"NO");

}
else{

fprintf(stdout,"YES");

}

fprintf(stdout, "\nAssign p[3] = p[0]");

point[3]=point[1];

fprintf(stdout, "\nModifying p[3]\n");


point_setSymbol(point[3], OUT);

if(point_print(stdout, point[3])<0){
    freepointers(point);
    return -1;
}

for(i=0; i<3; i++){
    if(point_print(stdout, point[i])<0){
        freepointers(point);
        return -1;
    
    }
}

freepointers(point);
return 0;

}



