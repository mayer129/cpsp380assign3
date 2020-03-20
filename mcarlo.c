/**
*  @author: Travis Mayer
*     ID: 002273275
*     Email: mayer129@mail.chapman.edu
*     Course: CPSC 353-01
*     Sources:
*       https://stackoverflow.com/questions/38704939/pass-argument-to-multiple-threads
*       https://stackoverflow.com/questions/19527965/cast-to-pointer-from-integer-of-different-size-pthread-code
*       A pthread example program by Silberschatz, Galvin, and Gagne
*
*/
#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void *runner(void *param); // thread
double random_double(); // returns double

int sum = 0; //sum variable

#define NUM_THREADS 2 // the number of threads

int main(int argc, char** argv)
{
 
    if (argc != 2) {
	    fprintf(stderr,"usage: ./mcarlo <integer value>\n");
	    return -1;
    }

    if (atoi(argv[1]) < 0) {
	    fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
	    return -1;
    }

    pthread_t tid[NUM_THREADS]; // the threads. default is 2. 
    int iterations = atoi(argv[1]); // number of input
    int *arg = malloc(sizeof(*arg)); // the argv[1]. have to do this so that we can divide the input evenly between all threads.
    *arg = iterations / NUM_THREADS;
  
    for (int i = 0; i < iterations; i++) { // creates the threads
        pthread_create(&tid[i], NULL, runner, arg);
    }
    for (int i = 0; i < iterations; i++) { // joins the threads
        pthread_join(tid[i], NULL);
    }
 
    printf("sum = %f\n",(4.0 * sum / iterations)); // prints the sum of the thread results
    
    free(arg); // frees the memory we allocated earlier
    return 0;
    
    
}
void *runner(void *param) {
    
    int hitCount = 0, npoints = *((int *) param); // have to do this for npoints so that the paramater will work
    for (int i = 0; i < npoints; i++) {
        // generate random numbers between -1.0 and +1.0 (exclusive)
        float x = random_double() * 2.0 - 1.0;
        float y = random_double() * 2.0 - 1.0;
        if (sqrt(x*x + y*y) < 1.0 )
            ++hitCount;
    }
    sum += hitCount;
    pthread_exit(0);
}

double random_double()
{
    return random() / ((double)RAND_MAX + 1);
}

