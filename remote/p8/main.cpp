#include <iostream>
#include "mpi.h"

#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

void print_tier(map<int, string> some_tier, char name[]) {
  printf("\n TIER %s:", name);
  for (auto const& node : some_tier)
  {
    printf(" | Node: %s Rank: %d", node.second.c_str(), node.first);
  }
}



int main(int argc, char** argv) {

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
  int rank,size, namelen;
  int send_num = 5;
  int received = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(node_name, &namelen);

  memset(node_name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);

//  printf("Node name is %s and its rank is %d 🔫 ", node_name, rank);

  // PART TWO

  map<int, string> tier_one;
  map<int, string> tier_two;

  if (rank <= size / 2) {
    tier_one.insert ( std::pair<int, string>(rank, node_name) );
  } else {
    tier_two.insert ( std::pair<int, string>(rank, node_name) );
  }

  MPI_Finalize();

  printf("Node name is %s and its rank is %d 🔫 ", node_name, rank);

//  print_tier(tier_one, "ONE");
//  print_tier(tier_two, "TWO");

  return 0;
}

