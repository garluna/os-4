extern long long counter;
extern int opt_yield;
extern pthread_mutex_t lock;

void add(long long *pointer, long long value);
void sum(void *a);
void mutexSum(void *a);
void spinSum(void *a);
void compareSum(void *a);

int createThreads(int numT, int numI, pthread_t* memory, char sync);
int joinThreads(int numT, int numI, pthread_t* memory);