#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define SIZE 10
#define GRIDSIZE 40
#define BOUNDARY 60
#define pi 3.141592

struct square{
    float angle;
    double xCorner;
    double yCorner;
} square1, square2;

typedef struct square Square;

void emptyGrid(char[GRIDSIZE][GRIDSIZE]);
void printGrid(char[GRIDSIZE][GRIDSIZE]);
void setCoordinate(char, char[GRIDSIZE][GRIDSIZE], double, double);
void setSquare(Square*, char[GRIDSIZE][GRIDSIZE]);
void emptySquare(Square*, char[GRIDSIZE][GRIDSIZE]);
float cot(float);
float rTan(float);
bool separation(Square*, Square*);

int main(){
    char grid[GRIDSIZE][GRIDSIZE];
//fill grid with spaces
    emptyGrid(grid);
//deg to rad, init struct variables
//square1
    square1.angle = 15   *(pi/180);
    square1.xCorner = 8;
    square1.yCorner = 8;
//square2
    square2.angle = 40    *(pi/180);
    square2.xCorner = 25;
    square2.yCorner = 25;
//out of bounds checks
    if(square1.xCorner > GRIDSIZE - SIZE || square1.yCorner > GRIDSIZE - SIZE){
        return 0;
    }
//declaration of function things
    Square* s1 = &square1;
    Square* s2 = &square2;
//Rotate a square
    int frames = 200;
    for(int i = 0; i < frames; i++){
        //Rotation and movement of Square 1
        square1.angle = (40*(pi/180))+i*(pi/180);
        square1.xCorner = 1+(i/10);
        square1.yCorner = 4+(i/10);
        //Rotation and movement of Square 2
        square2.angle = (40*(pi/180))+(i/2)*(pi/180);
        square2.xCorner = 35-(i/10);
        square2.yCorner = 28-(i/10);
        if(square1.angle == 0){
            square1.angle = 0.005;
        }
        if(square2.angle == 0){
            square2.angle = 0.005;
        }
        //placement of squares
        if(separation(s1,s2)==true){
            break;
        }
        setSquare(s1, grid);
        setSquare(s2, grid);
        printGrid(grid);
        //frame reset
        usleep(10000);
        system("clear");
        emptySquare(s1, grid);
        emptySquare(s2, grid);
    }
    printf("Collision detected - halting");
    return 0;
}



void emptyGrid(char g[GRIDSIZE][GRIDSIZE]){
   for(int i = 0; i < GRIDSIZE; i++){
        for(int j = 0; j < GRIDSIZE; j++){
            setCoordinate('.',g,i,j);
        }
    }
}

void printGrid(char g[GRIDSIZE][GRIDSIZE]){
    for(int i = 0; i < GRIDSIZE; i++){
        int a = GRIDSIZE-1-i;
        for(int j = 0; j < GRIDSIZE; j++){
            printf("%c", g[a][j]);
        }
        printf("\n");
    }
}

void setCoordinate(char c, char g[GRIDSIZE][GRIDSIZE], double x, double y){
    int a = x;
    int b = y;
    g[a][b]=c;
}

void setSquare(Square* s, char g[GRIDSIZE][GRIDSIZE]){
    double a = s->xCorner;
    double b = s->yCorner;
    float an = s->angle;
    for(float i = 0; i < SIZE; i+=0.25){
        for(float j = 0; j < SIZE; j+=0.25){
            double ax1 = a+(SIZE/2)+((i-(SIZE/2))*cos(an)-(j-(SIZE/2))*sin(an));
            double ax2 = b+(SIZE/2)+((i-(SIZE/2))*sin(an)+(j-(SIZE/2))*cos(an));
            if(ax1 < 0 || ax2 < 0 || ax1 > GRIDSIZE|| ax2 > GRIDSIZE){
            }else{
                setCoordinate('#', g, ax1, ax2);
            }
        }
    }
}

void emptySquare(Square* s, char g[GRIDSIZE][GRIDSIZE]){
    double a = s->xCorner;
    double b = s->yCorner;
    float an = s->angle;
    for(float i = 0; i < SIZE; i+=0.25){
        for(float j = 0; j < SIZE; j+=0.25){
            double ax1 = a+(SIZE/2)+((i-(SIZE/2))*cos(an)-(j-(SIZE/2))*sin(an));
            double ax2 = b+(SIZE/2)+((i-(SIZE/2))*sin(an)+(j-(SIZE/2))*cos(an));
            if(ax1 < 0 || ax2 < 0 || ax1 > GRIDSIZE|| ax2 > GRIDSIZE){
            }else{
                setCoordinate('.', g, ax1, ax2);
            }
        }
    }
}

float cot(float theta){
    if(sin(theta) == 0){
        theta = 0.005;
    }
    return (cos(theta)/sin(theta));
}

float rTan(float theta){
    if(cos(theta) == 0){
        theta = (pi/180)*90.005;
    }
    return (sin(theta)/cos(theta));
}

bool separation(Square* s1, Square* s2){
    //shape 1 is key
    //condition 1 for shape 1
    float s1p1c1 = (s1->xCorner)+cot(s1->angle)*(BOUNDARY-(s1->yCorner));
    float s1p2c1 = (s1->xCorner)-(SIZE*sin(s1->angle))+cot(s1->angle)*(BOUNDARY-(s1->yCorner)-(SIZE*cos(s1->angle)));
    float s2p1c1 = (s2->xCorner)+cot(s1->angle)*(BOUNDARY-(s2->yCorner));
    float s2p2c1 = (s2->xCorner)-(SIZE*sin(s2->angle))+cot(s1->angle)*(BOUNDARY-(s2->yCorner)-(SIZE*cos(s2->angle)));
    float s2p3c1 = (s2->xCorner)+(SIZE*cos(s2->angle))+cot(s1->angle)*(BOUNDARY-(s2->yCorner)-(SIZE*sin(s2->angle)));
    float s2p4c1 = (s2->xCorner)+(SIZE*(cos(s2->angle)-sin(s2->angle)))+cot(s1->angle)*(BOUNDARY-(s2->yCorner)-(SIZE*(cos(s2->angle)+sin(s2->angle))));
    // printf("%f\n%f\n%f\n%f\n%f\n%f\n\n\n", s1p1c1, s1p2c1, s2p1c1, s2p2c1, s2p3c1, s2p4c1);
    if(!(s1p1c1 < s2p1c1 && s2p1c1 < s1p2c1 ||
    s1p1c1 > s2p1c1 && s2p1c1 > s1p2c1 ||
    s1p1c1 < s2p2c1 && s2p2c1 < s1p2c1 ||
    s1p1c1 > s2p2c1 && s2p2c1 > s1p2c1 ||
    s1p1c1 < s2p3c1 && s2p3c1 < s1p2c1 ||
    s1p1c1 > s2p3c1 && s2p3c1 > s1p2c1 ||
    s1p1c1 < s2p4c1 && s2p4c1 < s1p2c1 ||
    s1p1c1 > s2p4c1 && s2p4c1 > s1p2c1)){
        return false;
    }
    //condition 2 for shape 1
    float s1p1c2 = (s1->xCorner)-rTan(s1->angle)*(BOUNDARY-(s1->yCorner));
    float s1p2c2 = (s1->xCorner)+(SIZE*cos(s1->angle))-rTan(s1->angle)*(BOUNDARY-(s1->yCorner)-SIZE*sin(s1->angle));
    float s2p1c2 = (s2->xCorner)-rTan(s1->angle)*(BOUNDARY-(s2->yCorner));
    float s2p2c2 = (s2->xCorner)-(SIZE*sin(s2->angle))-rTan(s1->angle)*(BOUNDARY-(s2->yCorner)-SIZE*cos(s2->angle));
    float s2p3c2 = (s2->xCorner)+(SIZE*cos(s2->angle))-rTan(s1->angle)*(BOUNDARY-(s2->yCorner)-SIZE*sin(s2->angle));
    float s2p4c2 = (s2->xCorner)-(SIZE*(sin(s2->angle)-cos(s2->angle)))-rTan(s1->angle)*(BOUNDARY-(s2->yCorner)-SIZE*(sin(s2->angle)+cos(s2->angle)));
    // printf("%f\n%f\n%f\n%f\n%f\n%f\n\n\n", s1p1c2, s1p2c2, s2p1c2, s2p2c2, s2p3c2, s2p4c2);
    if(!(s1p1c2 < s2p1c2 && s2p1c2 < s1p2c2 ||
    s1p1c2 > s2p1c2 && s2p1c2 > s1p2c2 ||
    s1p1c2 < s2p2c2 && s2p2c2 < s1p2c2 ||
    s1p1c2 > s2p2c2 && s2p2c2 > s1p2c2 ||
    s1p1c2 < s2p3c2 && s2p3c2 < s1p2c2 ||
    s1p1c2 > s2p3c2 && s2p3c2 > s1p2c2 ||
    s1p1c2 < s2p4c2 && s2p4c2 < s1p2c2 ||
    s1p1c2 > s2p4c2 && s2p4c2 > s1p2c2)){
        return false;
    }
    //shape 2 is now key
    //condition 3 for shape 2
    float s2p1c3 = (s2->xCorner)+cot(s2->angle)*(BOUNDARY-(s2->yCorner));
    float s2p2c3 = (s2->xCorner)-(SIZE*sin(s2->angle))+cot(s2->angle)*(BOUNDARY-(s2->yCorner)-(SIZE*cos(s2->angle)));
    float s1p1c3 = (s1->xCorner)+cot(s2->angle)*(BOUNDARY-(s1->yCorner));
    float s1p2c3 = (s1->xCorner)-(SIZE*sin(s1->angle))+cot(s2->angle)*(BOUNDARY-(s1->yCorner)-(SIZE*cos(s1->angle)));
    float s1p3c3 = (s1->xCorner)+(SIZE*cos(s1->angle))+cot(s2->angle)*(BOUNDARY-(s1->yCorner)-(SIZE*sin(s1->angle)));
    float s1p4c3 = (s1->xCorner)+(SIZE*(cos(s1->angle)-sin(s1->angle)))+cot(s2->angle)*(BOUNDARY-(s1->yCorner)-(SIZE*(cos(s1->angle)+sin(s1->angle))));
    // printf("%f\n%f\n%f\n%f\n%f\n%f\n\n\n", s2p1c3, s2p2c3, s1p1c3, s1p2c3, s1p3c3, s1p4c3);
    if(!(s2p1c3 < s1p1c3 && s1p1c3 < s2p2c3 ||
    s2p1c3 > s1p1c3 && s1p1c3 > s2p2c3 ||
    s2p1c3 < s1p2c3 && s1p2c3 < s2p2c3 ||
    s2p1c3 > s1p2c3 && s1p2c3 > s2p2c3 ||
    s2p1c3 < s1p3c3 && s1p3c3 < s2p2c3 ||
    s2p1c3 > s1p3c3 && s1p3c3 > s2p2c3 ||
    s2p1c3 < s1p4c3 && s1p4c3 < s2p2c3 ||
    s2p1c3 > s1p4c3 && s1p4c3 > s2p2c3)){
        return false;
    }
    //condition 4 for shape 2
    float s2p1c4 = (s2->xCorner)-rTan(s2->angle)*(BOUNDARY-(s2->yCorner));
    float s2p2c4 = (s2->xCorner)+(SIZE*cos(s2->angle))-rTan(s2->angle)*(BOUNDARY-(s2->yCorner)-SIZE*sin(s2->angle));
    float s1p1c4 = (s1->xCorner)-rTan(s2->angle)*(BOUNDARY-(s1->yCorner));
    float s1p2c4 = (s1->xCorner)-(SIZE*sin(s1->angle))-rTan(s2->angle)*(BOUNDARY-(s1->yCorner)-SIZE*cos(s1->angle));
    float s1p3c4 = (s1->xCorner)+(SIZE*cos(s1->angle))-rTan(s2->angle)*(BOUNDARY-(s1->yCorner)-SIZE*sin(s1->angle));
    float s1p4c4 = (s1->xCorner)-(SIZE*(sin(s1->angle)-cos(s1->angle)))-rTan(s2->angle)*(BOUNDARY-(s1->yCorner)-SIZE*(sin(s1->angle)+cos(s1->angle)));
    printf("%f\n%f\n%f\n%f\n%f\n%f\n\n\n", s2p1c4, s2p2c4, s1p1c4, s1p2c4, s1p3c4, s1p4c4);
    if(!(s2p1c4 < s1p1c4 && s1p1c4 < s2p2c4 ||
    s2p1c4 > s1p1c4 && s1p1c4 > s2p2c4 ||
    s2p1c4 < s1p2c4 && s1p2c4 < s2p2c4 ||
    s2p1c4 > s1p2c4 && s1p2c4 > s2p2c4 ||
    s2p1c4 < s1p3c4 && s1p3c4 < s2p2c4 ||
    s2p1c4 > s1p3c4 && s1p3c4 > s2p2c4 ||
    s2p1c4 < s1p4c4 && s1p4c4 < s2p2c4 ||
    s2p1c4 > s1p4c4 && s1p4c4 > s2p2c4)){
        return false;
    }
    return true;
}