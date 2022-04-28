/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 C = B x A x At + Bt x B
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");

	double *BA = calloc(N * N, sizeof(double));

	if (BA == NULL) 
		exit(-1);

	// solving BxA
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k <= j; k++) {
				BA[N * i + j] += B[N * i + k] * A[N * k + j];
			}
		}
	}

	double *BAAt = calloc(N * N, sizeof(double));
	
	if (BAAt == NULL) 
		exit(-1);

	// solving BxAxAt
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				BAAt[N * i + j] += BA[N * i + k] * A[N * j + k];
			}
		}
	}

	double *BtB = calloc(N * N, sizeof(double));
	
	if (BtB == NULL) 
		exit(-1);

	// solving BtxB
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				BtB[N * i + j] += B[N * k + i] * B[N * k + j];
			}
		}
	}

	double *C = calloc(N * N, sizeof(double));
	
	if (C == NULL) 
		exit(-1);

	// solving C = BxAxAt + BtxB
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[N * i + j] = BAAt[N * i + j] + BtB[N * i + j];
		}
	}

	free(BA);
	free(BAAt);
	free(BtB);
	return C;
}
