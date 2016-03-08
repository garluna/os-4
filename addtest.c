void add(long long *pointer, long long value)
{
    long long sum = *pointer + value;
    *pointer = sum;
}

void sum(void *a, long long count)
{
	int n = *(int*)a;
	for (int i = 0; i < n; i++) //++ i or i++
	{
		add(&count, 1);
	}

	for(int i = 0; i < n; i++)
	{
		add(&count, -1);
	}
}

pthread_t* threads = malloc(num_threads*sizeof(pthread_t));

for (i = 0; i < num_threads; i++) 
{
  	ret = pthread_create(threads[i], NULL, (void *) &sum, (void *)&num_iter);
  	if (ret != 0) {
  		fprintf(stderr, "ERROR: thread creation: error code is %d\n", ret);
  		exit(1);
  	}
}

  for (i = 0; i < num_threads; i++) {
  	ret = pthread_join(threads[i], NULL);
  	if (ret != 0) {
  		fprintf(stderr, "ERROR: joining threads: error code is %d\n", ret);
  		exit(1);
  	}
  }
