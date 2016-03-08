#include <stdio.h>
#include <pthread.h>

long long counter = 0;

void add(long long *pointer, long long value)
{
    long long sum = *pointer + value;
    *pointer = sum;
}

void sum(void *a)
{
	int n = *(int*)a;
	for (int i = 0; i < n; i++) //TACO ++ i or i++
	{
		add(&counter, 1);
	}

	for(int i = 0; i < n; i++)
	{
		add(&counter, -1);
	}
}

int createThreads(int numT, int numI, pthread_t* memory)
{
	int i;
	int j;
	for (i = 0; i < numT; i++) 
	{
  		j = pthread_create(&memory[i], NULL, (void *)&sum, (void *)&numI);
  		if (j != 0) 
  		{
  			fprintf(stderr, "ERROR: thread creation: error code is %d\n", j);
  			//TACO do something with exit status
  		}
	}
}

int joinThreads(int numT, int numI, pthread_t* memory)
{
	int i;
	int j;
	for (i = 0; i < numT; i++) 
	{
  		j = pthread_join(memory[i], NULL);
  		if (j != 0) 
  		{
  			fprintf(stderr, "ERROR: joining threads: error code is %d\n", j);
  			//TACO do something with exit status
  		}
  	}

}