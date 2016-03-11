#define _GNU_SOURCE   
#include <stdio.h>
#include <pthread.h>

#include "addtest.h"

long long counter = 0;
int opt_yield = 0;

static pthread_mutex_t lock;
volatile static int lock2 = 0;

void add(long long *pointer, long long value)
{
    long long sum = *pointer + value;
    if (opt_yield)
        pthread_yield();
    *pointer = sum;
}

void sum(void *a)
{
	int n = *(int*)a;
	for (int i = 0; i < n; i++) 
	{
		add(&counter, 1);
	}

	for(int i = 0; i < n; i++)
	{
		add(&counter, -1);
	}
}

void mutexSum(void *a)
{
	int n = *(int *)a;
	for (int i = 0; i < n; i++) 
	{
		pthread_mutex_lock(&lock);
		add(&counter, 1);
		pthread_mutex_unlock(&lock);
	}
	for (int i = 0; i < n; ++i) 
	{
		pthread_mutex_lock(&lock);
		add(&counter, -1);
		pthread_mutex_unlock(&lock);
	}
}

void spinSum(void *a)
{
	int n = *(int *)a;
	for (int i = 0; i < n; i++) 
	{
		while(__sync_lock_test_and_set(&lock2, 1))
		{
			continue;
		}
		add(&counter, 1);
		__sync_lock_release(&lock2);
	}
	for (int i = 0; i < n; i++)
	{
		while(__sync_lock_test_and_set(&lock2, 1))
		{
			continue;
		}
		add(&counter, -1);
		__sync_lock_release(&lock2);
	}
}

void compareSum(void *a)
{
	int n = *(int *)a;
	int tmp;
	long long* countPtr = &counter;
	long long csum;
	for (int i = 0; i < n; i++)
	{
		do 
		{
			tmp = *countPtr;
			csum = tmp + 1;
      		if (opt_yield) 
      			pthread_yield();
		} while(__sync_val_compare_and_swap(countPtr, tmp, csum)!= tmp);
	}
	for (int i = 0; i < n; i++) 
	{
		do
		{
			tmp = *countPtr;
			csum = tmp - 1;
      		if (opt_yield) 
      			pthread_yield();
		} while(__sync_val_compare_and_swap(countPtr, tmp, csum)!= tmp);
	}
}

int createThreads(int numT, int numI, pthread_t* memory, char sync)
{
	int i;
	int j;
	int exitStat = 0;
	for (i = 0; i < numT; i++) 
	{
		switch(sync)
		{
			case 'a':
			{
				j = pthread_create(&memory[i], NULL, (void *)&sum, (void *)&numI);
  				if (j != 0) 
  				{
  					fprintf(stderr, "ERROR: thread creation, error code: %d\n", j);
  					//TACO do i add a break here
  					exitStat = 1;
  					//break;
					return exitStat;
  				}
				break;
			}
			case 'm':
			{
				j = pthread_create(&memory[i], NULL, (void *)&mutexSum, (void *)&numI);
  				if (j != 0) 
  				{
  					fprintf(stderr, "ERROR: thread creation, error code: %d\n", j);
  					exitStat = 1;
  					//break;
					 return exitStat;
  				}
				break;
			}
			case 's':
			{
				j = pthread_create(&memory[i], NULL, (void *)&spinSum, (void *)&numI);
  				if (j != 0) 
  				{
  					fprintf(stderr, "ERROR: thread creation, error code: %d\n", j);
  					exitStat = 1;
					return exitStat;
  				}
				break;
			}
			case 'c':
			{
				j = pthread_create(&memory[i], NULL, (void *)&compareSum, (void *)&numI);
  				if (j != 0) 
  				{
  					fprintf(stderr, "ERROR: thread creation, error code: %d\n", j);
  					exitStat = 1;
					return exitStat;
  				}
				break;
			}
		}
	}
	return exitStat;
}

int joinThreads(int numT, int numI, pthread_t* memory)
{
	int i;
	int j;
	int exitStat = 0;
	for (i = 0; i < numT; i++) 
	{
  		j = pthread_join(memory[i], NULL);
  		if (j != 0) 
  		{
  			fprintf(stderr, "ERROR: joining threads: error code is %d\n", j);
  			exitStat = 1;
  		}
  	}
  	return exitStat;
}