#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[]) {
	long long int j, largeN;
	double sum = 0.0;
	clock_t tstart, tend;
	int num_dev;

	num_dev = omp_get_num_devices();

	printf("%d\n", num_dev);

	largeN = (long long int) atoll(argv[1]);

	printf("Large Number = %lld\n", largeN);

	tstart = clock();
#pragma omp parallel for private(j) reduction(+:sum)
	for(j=1; j<largeN; j++) {
		sum += (double) (1.0/j);
	}
	tend = clock();
	printf("Sum [1, ... , %lld] = %.6f\n", largeN, sum);
	printf("\nCompleted in %.2f seconds%45s\n\n", ( (double) (tend - tstart) ) / CLOCKS_PER_SEC, "");

	sum = 0.0;
	tstart = clock();
#pragma omp target map(to:largeN) map(tofrom:sum)
#pragma omp parallel for simd private(j) reduction(+:sum)
	for (j=1; j<largeN; j++) {
		sum += (double) (1.0/j);
	}
	tend = clock();
	printf("Sum [1, ... , %lld] = %.6f\n", largeN, sum);
	printf("\nCompleted in %.2f seconds%45s\n\n", ( (double) (tend - tstart) ) / CLOCKS_PER_SEC, "");

	return(0);
}
