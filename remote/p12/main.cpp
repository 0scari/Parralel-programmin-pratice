#include <iostream>
#include "mpi.h"
#include "omp.h"
#include <stdio.h>
#include <string.h>
#include <array>
#include <unistd.h>
#include <limits>

#define INT_ARRAY_SIZE 10

using namespace std;

struct Node {
    char name[MPI_MAX_PROCESSOR_NAME];
    int rank;
    int comm_size;
    array<int, INT_ARRAY_SIZE> integers;
} this_node;

void instruct_swapping(int node1, int node2) {
  printf("\n\nInstructing array swapping between nodes %d and %d\n", node1, node2);
  array<int, 2> swap_instruction = {node1, node2};
  for (int i = 1; i < 8; ++i) {
    MPI_Send(&swap_instruction, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
  }
}

void swap_arrays(int node1, int node2) {
  if (this_node.rank == node1) {
    MPI_Send(&this_node.integers, INT_ARRAY_SIZE, MPI_INT, node2, 0, MPI_COMM_WORLD);
    MPI_Recv(&this_node.integers, INT_ARRAY_SIZE, MPI_INT, node2 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("\nNode %d completed swapping\n", node1);
  } else if (this_node.rank == node2) {
    array<int, INT_ARRAY_SIZE> temp = this_node.integers;
    MPI_Recv(&this_node.integers, INT_ARRAY_SIZE, MPI_INT, node1 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&temp, INT_ARRAY_SIZE, MPI_INT, node1, 0, MPI_COMM_WORLD);
    printf("\nNode %d completed swapping\n", node2);
  }
}

void receive_on_head_node() {
  int v1, v2, v3, v4, v5, v6 ,v7;
  MPI_Recv(&v1, 1, MPI_INT, 1 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nHead node received min value %d from node 1", v1);
  MPI_Recv(&v2, 1, MPI_INT, 2 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nHead node received min value %d from node 2", v2);
  MPI_Recv(&v3, 1, MPI_INT, 3 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nHead node received min value %d from node 3", v3);
  MPI_Recv(&v4, 1, MPI_INT, 4 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nHead node received min value %d from node 4", v4);
  MPI_Recv(&v5, 1, MPI_INT, 5 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nHead node received min value %d from node 5", v5);
  MPI_Recv(&v6, 1, MPI_INT, 6 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nHead node received min value %d from node 6", v6);
  MPI_Recv(&v7, 1, MPI_INT, 7 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("\nHead node received min value %d from node 7\n", v7);
}

void generate_randint_array(array<int, INT_ARRAY_SIZE> &array) {
  for (int i = 0; i < INT_ARRAY_SIZE; ++i) {
    array[i] = rand() % 50;
  }
}

string get_string_repr(array<int, INT_ARRAY_SIZE> integers) {
  string result = "[";
  for (int i = 0; i < INT_ARRAY_SIZE; ++i) {
    result += to_string(integers[i]);
    if (i < INT_ARRAY_SIZE - 1) {
      result += ", ";
    }
  }
  result += "]";
  return result;
}

void send_to_all_nodes() {
  array<int, INT_ARRAY_SIZE> integers;
  for (int i = 1; i < 8; ++i) {
    generate_randint_array(integers);
    MPI_Send(&integers, INT_ARRAY_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
    printf("\n✉️ An integer list %s was sent  to node %d", get_string_repr(integers).c_str() ,i);
  }
}


int main(int argc, char** argv) {

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  int namelen, numprocs;
  MPI_Comm_rank(MPI_COMM_WORLD, &this_node.rank);
  MPI_Comm_size(MPI_COMM_WORLD, &this_node.comm_size);

  MPI_Get_processor_name(this_node.name, &namelen);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  memset(this_node.name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);

  if (this_node.rank == 0) {
    send_to_all_nodes();
    instruct_swapping(rand() % 7 + 1, rand() % (numprocs - 1) + 1);
    receive_on_head_node();
  } else {
    MPI_Recv(&this_node.integers, INT_ARRAY_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf(" 📬 Node %d has received a list of integers: %s | ", this_node.rank, get_string_repr(this_node.integers).c_str());

    array<int, 2> swap_instruction;
    MPI_Recv(&swap_instruction, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (this_node.rank == swap_instruction[0] || this_node.rank == swap_instruction[1]) {
      swap_arrays(swap_instruction[0], swap_instruction[1]);
    }

    int x = numeric_limits<int>::max(); // i.e. infinity
    #pragma omp parallel for reduction(min:x)
    for (int i=0; i<INT_ARRAY_SIZE; i++) {
      x = min(x,this_node.integers[i]);
    }
    printf(" Node %d, min = %d | ", this_node.rank, x);
    MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}