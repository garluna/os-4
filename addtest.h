extern long long counter;

void add(long long *pointer, long long value);
void sum(void *a);

//int createThreads(int numT, int numI, pthread_t* memory, long long counter);
//int joinThreads(int numT, int numI, pthread_t* memory, long long counter);

int createThreads(int numT, int numI, pthread_t* memory);
int joinThreads(int numT, int numI, pthread_t* memory);