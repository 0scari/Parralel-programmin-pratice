#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

int main (void)
{
    int matrix[2][2] = {{1, 2}, {3, 4}};
    int rand_index = (rand() % (sizeof(matrix[0])/sizeof(*matrix[0])) - 1) + 0;
    int sum = 0;

#pragma omp parallel for schedule(dynamic) private(rand_index) reduction(+: sum)
    for (int i = 0; i < 2; ++i) {
        sum += matrix[rand_index][i];
    };

    printf("matrix[2][2] = {{1, 2}, {3, 4}}\n");
    printf("Random matrix index: %d and sum: %d\n", rand_index, sum);

    // PART TWO
    printf( "\n\nPART TWO");
//
//    vector<vector<int> > vector_vector;
//    vector<int> vector_one;
//    vector_one.push_back(5);
//    vector_one.push_back(3);
//    vector_vector.push_back(vector_one);
//
//    vector<int> vector_two;
//    vector_two.push_back(50);
//    vector_two.push_back(30);
//
//    printf("\n\nIteration");

//    for (int i = 0; i < 2; ++i) {
//        printf("\n\nIteration %d", i);
//        #pragma omp parallel for private(vector_vector) reduction(+: sum_two)
//        for (int j = 0; j < 2; ++j) {
//            sum_two += vector_vector[0][j];
//            printf("\nadding %d", vector_vector[0][j]);
//        }
//        printf("\nΣ = %d", sum_two);
//        if (i == 0) {
//            sum_two = 0;
//            vector_vector[0] = vector_two;
//        }
};

//    printf("\n");
return 0;
}
