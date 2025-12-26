//generate 50 random numbers between [-0.5, 0.5] and store them in a rand.dat file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("rand.dat", "w");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    srand((unsigned int)time(NULL)); // srand works with unsigned int seed thus casting time to unsigned int and initializing random number generator with current time

    for (int i = 0; i < 50; i++) {
        double random_number = ((double)rand() / RAND_MAX) - 0.5; //rand used to generate number between [0,1], scale to [-0.5,0.5] by dividing by RAND_MAX and subtracting 0.5
        fprintf(file, "%lf\n", random_number);
    }

    fclose(file);
    return 0;
}