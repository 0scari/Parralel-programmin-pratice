#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <stdio.h>


using namespace std;

int main (void) {

#pragma omp parallel
    {
        for (int i = 0; i < 1000; ++i) {
            printf("%d, ", i);
        }
    }

    cout << "\n\nParallel For now\n\n";
    sleep(2);

#pragma omp parallel for
    for (int i = 0; i < 1000; ++i) {
        printf("%d, ", i);
    }

    // PART TWO
    cout << "\n\nPART TWO\n\n";


    int sum = 0;

    int matrix[3][2];
    cout << "Matrix: [ ";
    for (int i = 0; i < 3; ++i) {
        cout << "[ ";
        for (int j = 0; j < 2; ++j) {
            int val = (rand() % 5) + 0;
            matrix[i][j] = val;
            printf("%d, ", val);
        }
        cout << "]";
    }
    cout << " ]";

#pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < (sizeof(matrix)/sizeof(*matrix)); ++i) {
        sum += matrix[i][0] + matrix[i][1];
        printf("\nAdding %d to the total from matrix[%d][0]", matrix[i][0], i);
        printf("\nAdding %d to the total from matrix[%d][1]", matrix[i][1], i);
    };
    printf("\nΣ = %d\n", sum);
}

