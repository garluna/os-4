#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "parser.h"
#include "addtest.h"

int main(int argc, char** argv)
{
	int exit_status;
	int oper = 0;

	struct timespec start;
	struct timespec end;
	long long startTime;
	long long endTime;
	long long totalTime;

	if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
	{
		fprintf(stderr, "ERROR: clock_gettime start time\n");
		exit(1);
	}

	exit_status = parser(argc, argv);
	if (exit_status)
	{
		exit(exit_status);
	}

	if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
	{
		fprintf(stderr, "ERROR: clock_gettime end time\n");
		exit(1);
	}

	startTime = (long long)(start.tv_sec*pow(10, 9) + start.tv_nsec);
	endTime = (long long)(end.tv_sec*pow(10, 9) + end.tv_nsec);
	totalTime = endTime - startTime;
	oper = numThreads * numIter * 2;

	printf("%d threads x %d iterations x (add + subtract) = %d operations\n", numThreads, numIter, oper);

	if (counter != 0)
	{
  		fprintf(stderr, "ERROR: final count = %lld\n", counter);
  		exit_status = 1;
	}
  	printf("elapsed time: %lld ns\n", totalTime);
	printf("per operation: %lld ns\n", totalTime/oper);

	exit(exit_status);
}