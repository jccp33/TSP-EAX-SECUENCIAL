
// compile GCC:  gcc main.c -o main -lpthread -lm
// run:          time ./main

#include "outs.c"

int main(int argc, char **argv){
	srand(time(NULL));
	InputFile();
	CalculateCost();
	int max_x = GetMaxX();
	int max_y = GetMaxY();
	int best_indiv_id, worst_indv_id;

	// PrintData();
	// PrintCost(20);
	// PrintNNlist(20);

	int ave_conv_gen = 0;
	float ave_exe_time = 0.0;
	float ave_final_error = 0.0;
	for(int trial=0; trial<TRIAL; trial++){

		clock_t t_start, t_end;
		double secs = 0;
		double total_time = 0;
		t_start = clock();
		for(int i=0; i<POPULATION; i++){
			InitTwoOpt(popul[i]);
		}
		t_end = clock();
		secs = (double)(t_end - t_start) / CLOCKS_PER_SEC;
		total_time += secs;

		int best_child_id = 0;
		best_indiv_id = GetBestIndividualID();
		worst_indv_id = GetWorstIndividualID();
		char iter_str[50];
		int best_indiv_fitness = 1000000;
		int worst_indv_fitness = 0;
		printf("AG SECUENCIAL - TRIAL %d\n", trial);
		printf("GEN\tMIN\tMAX\tPROM\tERROR\tTIME(s)\n");
		printf("------------------------------------------------\n");
		int avg = 0;
		for(int i=0; i<POPULATION; i++) avg += popul[i][DIMENSION];
		float error = ((float)popul[best_indiv_id][DIMENSION] - (float)BEST_OLIB) / (float)BEST_OLIB * 100;
		int generation = 1;
		printf("%d\t%d\t%d\t%d\t%.2f\t%.2f\n", generation, popul[best_indiv_id][DIMENSION], popul[worst_indv_id][DIMENSION], (avg)/POPULATION, error, secs);

		for(int gener=0; gener<GENERATION; gener++){
			t_start = clock();
			for(int i=0; i<POPULATION-1; i++){
				EAX(i, i+1, max_x, max_y);
			}
			EAX(POPULATION-1, 0, max_x, max_y);
			t_end = clock();
			secs = (double)(t_end - t_start) / CLOCKS_PER_SEC;
			total_time += secs;
			// get best individual
			best_indiv_id = GetBestIndividualID();
			worst_indv_id = GetWorstIndividualID();
			if(popul[best_indiv_id][DIMENSION] < best_indiv_fitness){
				best_indiv_fitness = popul[best_indiv_id][DIMENSION];
			}
			avg = 0;
			for(int i=0; i<POPULATION; i++) avg += popul[i][DIMENSION];
			error = ((float)popul[best_indiv_id][DIMENSION] - (float)BEST_OLIB) / (float)BEST_OLIB * 100;
			generation++;
			printf("%d\t%d\t%d\t%d\t%.2f\t%.2f\n", generation, popul[best_indiv_id][DIMENSION], popul[worst_indv_id][DIMENSION], (avg)/POPULATION, error, secs);
			if(error < ERROR) break;
			ShufflePopulation();
		}

		ave_conv_gen += generation;
		ave_exe_time += total_time/60.0;
		ave_final_error += error;
	}

	printf("\n\n");
	printf("TOTAL EXECUTIONS................. %d\n", TRIAL);
	printf("AVERAGE CONVERGENCE GENERATION... %d\n", ave_conv_gen/TRIAL);
	printf("AVERAGE FINAL ERROR.............. %.4f\n", ave_final_error/(float)TRIAL);
	printf("AVERAGE EXECUTION TIME (min)..... %.4f\n\n", ave_exe_time/(float)TRIAL);

	// PlotIndividual(popul[best_indiv_id], "blue", "2", max_x, max_y);

	printf("\n");
	return 0;
}
