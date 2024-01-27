#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int size = 10000;

    int *randomArray = (int *)malloc(size * sizeof(int));

    if (randomArray == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the array with random values
    for (int i = 0; i < size; i++) {
        randomArray[i] = rand();
    }


    double sum=0.0; int i;
    #pragma omp parallel for reduction(+:sum)
    for (i=0; i<size; i++)
    {
        sum += randomArray[i];
    }
    free(randomArray);

    printf("The average is %f\n", sum/size);
    return 0; // Exit successfully
}
