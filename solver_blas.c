/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include "cblas.h"

/* 
 * Add your BLAS implementation here
  C = B x A x At + Bt x B
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");

	double *BA = calloc(N * N, sizeof(double));
	
	if (BA == NULL) 
		exit(-1);

	double *BAAt = calloc(N * N, sizeof(double));
	
	if (BAAt == NULL) 
		exit(-1);

	double *BtB = calloc(N * N, sizeof(double));
	
	if (BtB == NULL) 
		exit(-1);

	for (int i = 0; i < N * N; i++) {
		BA[i] = A[i];
		BAAt[i] = A[i];
		BtB[i] = B[i];
	}

	// solving BxA
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, 
		CblasNonUnit, N, N, 1, B, N, BA, N);

	// solving BxAxAt
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans,
		CblasNonUnit, N, N, 1, BAAt, N, BA, N);

	// solving BtxB + BxAxAt
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N,
	 	1, BtB, N, B, N, 1, BA, N);

	free(BAAt);
	free(BtB);

	return BA;
}
