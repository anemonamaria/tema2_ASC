/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
   C = B x A x At + Bt x B
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	double *Bt = calloc(N * N, sizeof(double));

	if (Bt == NULL) 
		exit(-1);

	double *At = calloc(N * N, sizeof(double));

	if (At == NULL) 
		exit(-1);	

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			At[i * N + j] = A[j * N + i];
			Bt[i * N + j] = B[j * N + i];
		}
	}
	
	double *BA = calloc(N * N, sizeof(double));

	if (BA == NULL) 
		exit(-1);

	// solving BxA
	// B LINES x A COLUMNS = B LINES x At LINES 
	for (register int i = 0; i < N; i++) {
		register double *fst = &B[i * N];
		for (register int j = 0; j < N; j++) {
			register double *snd = &At[j * N];
			register double *sndfst = fst;
			register double sum = 0;
			for (register int k = 0; k < N; k++) {
				sum += *sndfst * *snd;
				sndfst++;
				snd++;
			}
			BA[N * i + j] = sum;
		}
	}

	double *C = calloc(N * N, sizeof(double));
	
	if (C == NULL) 
		exit(-1);

	// solving BxAxAt
	// BA LINES x At COLUMS = BA LINES x A LINES
	for (register int i = 0; i < N; i++) {
		register double *fst = &BA[i * N];
		for (register int j = 0; j < N; j++) {
			register double *sndfst = fst;
			register double *snd = &A[j * N];
			register double sum = 0;
			for (register int k = 0; k < N; k++) {
				sum += *sndfst * *snd;
				sndfst++;
				snd++;
			}
			C[N * i + j] += sum;
		}
	}

	// solving BtxB
	// Bt LINES x B COLUMNS = Bt LINES x BT LINES
	for (int i = 0; i < N; i++) {
		register double *fst = &Bt[i * N];
		for (int j = 0; j < N; j++) {
			register double sum = 0.0;
			register double *snd = &Bt[j * N];
			register double *sndfst = fst;
			for (int k = 0; k < N; k++) {
				sum += *sndfst * *snd;
				sndfst++;
				snd++;
			}
			C[N * i + j] += sum;
		}
	}

	free(BA);
	free(Bt);
	free(At);
	return C;
}
