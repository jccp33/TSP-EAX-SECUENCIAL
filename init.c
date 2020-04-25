
#include "funct.c"

void InitTwoOpt(int *H){
    int count = 0, rnd = 0, fitness = 0;
    for(int i=0; i<DIMENSION; i++) H[i] = i;
    
    int post1, post2, aux;
    for(int i=0; i<DIMENSION; i++){
        post1 = rand() % DIMENSION;
        post2 = rand() % DIMENSION;
        aux = H[post1];
        H[post1] = H[post2];
        H[post2] = aux;
    }

    //PlotIndividual(H, "indv.dat", "black", "2", 110, 50);

    // two opt
    int p1, p2, p3, p4, t3, t4, tmp_distance, max_distance;
    int depth;
    int list_itr;

    int improve = 1; 
    while(improve){
        improve = 0;
        for(int i=0; i<DIMENSION; i++){
            max_distance = 0; // distancia
            p1 = i; p2 = (i + 1) % DIMENSION; depth = 0; list_itr = 1;
            while(depth < DEPTH){
                for(int j=0; j<DIMENSION; j++){
                    if(H[j] == NNlist[H[p1]][list_itr].id){
                        t3 = j; t4 = (j + 1) % DIMENSION; break;
                    }
                }
                tmp_distance = cost[H[p1]][H[p2]] + cost[H[t3]][H[t4]] - cost[H[p1]][H[t3]] - cost[H[p2]][H[t4]];
                if(max_distance < tmp_distance){
                    max_distance = tmp_distance; p3 = t3; p4 = t4;
                }
                depth++;
                list_itr++;
            }
            if(max_distance > 0){
                if(p2 < p3){
                    for(int k = 0; k < (p3 - p2 + 1) / 2; k++){
                        aux = H[p2 + k]; H[p2 + k] = H[p3 - k]; H[p3 - k] = aux;
                    }
                }else{
                    for(int k = 0; k < (DIMENSION - (p2 - p3) + 1) / 2; k++){
                        aux = H[(p2 + k) % DIMENSION]; H[(p2 + k) % DIMENSION] = H[(p3 - k + DIMENSION) % DIMENSION];
                        H[(p3 - k + DIMENSION) % DIMENSION] = aux;
                    }
                }
                improve = 1;
            }
        }
    }

    H[DIMENSION] = EvaluateFitness(H);

    //PlotIndividual(H, "indv.dat", "black", "2", 110, 50);
}



