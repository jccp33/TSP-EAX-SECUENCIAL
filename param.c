
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define INPUT_FILE    "./TSPLIB/xqf131.tsp"
#define DIMENSION     131
#define BEST_OLIB     564
#define GENERATION    100
#define POPULATION    80
#define CHILDREN      40
#define DEPTH         20
#define ERROR         0.1
#define TRIAL         10

struct PAIR{
    int id;
    int dist;
};

int data[DIMENSION][3];
int cost[DIMENSION][DIMENSION];
struct PAIR NNlist[DIMENSION][DIMENSION];
int popul[POPULATION][DIMENSION+1];
