#include <iostream>
#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

struct Node {
    char name[MPI_MAX_PROCESSOR_NAME];
    int rank;
    int comm_size;
} this_node;

void send_to_node(int node_rank, int value) {
  MPI_Send(&value, 1, MPI_INT, node_rank, 0, MPI_COMM_WORLD);
}

int main(int argc, char** argv) {

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  int namelen;
  MPI_Comm_rank(MPI_COMM_WORLD, &this_node.rank);
  MPI_Comm_size(MPI_COMM_WORLD, &this_node.comm_size);

  MPI_Get_processor_name(this_node.name, &namelen);
  memset(this_node.name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);

  // random selection is impossible as every node runs this code
  int sender = 0,
      receiver = 1;
  int value;

  if (this_node.rank == sender) {
    send_to_node(receiver, (rand() % 7) + 4);
    MPI_Recv(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("%s received value %d from node %d\n",
           this_node.name, value, receiver);
  } else if (this_node.rank == receiver) {
    MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("%s received value %d from node %d\n",
           this_node.name, value, sender);
    send_to_node(sender, value + 2);
  }

  MPI_Finalize();

  return 0;
}