#include <iostream>
#include "mpi.h"
#include "omp.h"
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

void processing_func(int &sum, int number) {
  sum += number;
}

int data[8][8] = {
        {1,2,3,4,5,6,7,21},
        {1,2,3,4,5,6,7,1},
        {3,2,3,2,5,6,7,5},
        {1,2,3,4,5,6,7,8},
        {1,2,1,4,9,6,4,8},
        {4,2,3,4,5,6,7,8},
        {1,1,43,4,8,6,2,8},
        {1,2,3,4,3,6,7,11},
};

void send_to_head_node(int value) {
  int head_node = 0;
  MPI_Send(&value, 1, MPI_INT, head_node, 0, MPI_COMM_WORLD);
}

void receive_on_head_node(int v0) {
  printf("Head node calculation is %d", v0);
  
  int v1, v2, v3, v4, v5, v6 ,v7;
  MPI_Recv(&v1, 1, MPI_INT, 1 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nReceived calculation %d from node 1", v1);
  MPI_Recv(&v2, 1, MPI_INT, 2 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nReceived calculation %d from node 2", v2);
  MPI_Recv(&v3, 1, MPI_INT, 3 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nReceived calculation %d from node 3", v3);
  MPI_Recv(&v4, 1, MPI_INT, 4 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nReceived calculation %d from node 4", v4);
  MPI_Recv(&v5, 1, MPI_INT, 5 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nReceived calculation %d from node 5", v5);
  MPI_Recv(&v6, 1, MPI_INT, 6 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nReceived calculation %d from node 6", v6);
  MPI_Recv(&v7, 1, MPI_INT, 7 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nReceived calculation %d from node 7", v7);

  printf("\nSum = %d\n",v0 + v1 + v2 + v3 + v4 + v5 + v6 + v7);

}


int main(int argc, char** argv) {

  int numprocs, rank, namelen;
  char node_name[MPI_MAX_PROCESSOR_NAME];
  int thread_no = 0, thread_count = 1;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(node_name, &namelen);

  // Part One
  #pragma omp parallel private(thread_no, thread_count)
  {
    thread_no = omp_get_thread_num();
    thread_count = omp_get_num_threads();
    printf("I'm processor %d out of %d on %s with rank %d out of %d\n",
           thread_no, thread_count, node_name, rank, numprocs);
  }

  // Part Two
  int sum = 0;
  #pragma omp parallel private(thread_no) reduction(+: sum)
  {
    thread_no = omp_get_thread_num();
    processing_func(sum, data[rank][thread_no]);
  }

  if (rank != 0) {
    send_to_head_node(sum);
  } else {
    receive_on_head_node(sum);
  }

  MPI_Finalize();

  return 0;
}

