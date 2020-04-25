
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "xqf131.tsp"
#define DIMENSION  131

int data[DIMENSION][3];

int main(int argc, char **argv){
    FILE *file = fopen(INPUT_FILE, "rb");
    char buffer[255];
    int fscanf_r = 0;
	if(file == NULL){
		printf("*** FILE DONT FOUND ***\n");
	}else{
		int cont = 0;
        printf("\n");
		while(fgets(buffer, 255, (FILE*) file)){
            if(cont>=5 && cont<6+DIMENSION){
                fscanf_r = fscanf(file, "%d %d %d", &data[cont-5][0], &data[cont-5][1], &data[cont-5][2]);
                data[cont-5][0] = data[cont-5][0] - 1;
                // printf("*** FILE RESPONCE: %d ***\n", fscanf_r);
            }
            cont++;
        }
	}
	fclose(file);

    FILE *file2 = fopen("plot_points.dat", "w");
    fprintf(file2, "#\tX\tY\n");
    for(int i=0; i<DIMENSION; i++){
        fprintf(file2, "\t%d\t%d\n", data[i][1], data[i][2] );
    }
    fclose(file2);

    printf("\n");
    return 0;
}
