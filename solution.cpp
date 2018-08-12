#include <bits/stdc++.h>
#include <sys/resource.h>
using namespace std;
#include "State.h"
#include "Table.h"
#include "Algorithms/dfs.h"
#include "Algorithms/bfs.h"
#include "Algorithms/aStar.h"
#include "init.h"
#define DEBUG if(0)
#define lli long long int

int main(int argc, char **argv)
{
  init;

  size = atoi(argv[1]); int runs = atoi(argv[2]), verbose = atoi(argv[3]);
  for (int i = 0; i < size; i ++) table.push_back(vector<int>(size));
  int aa = 0, bb = 0, aaa = 0, bbb = 0, ss, sss;
  while (runs --)
  {
    scramble();
    if (verbose) printTable();
    vector<vector<int> > aux = table;
    int si, sj;
    for (int i = 0; i < size; i ++) for (int j = 0; j < size; j ++) if (table[i][j] == 0) si = i, sj = j;

    // printf("DFS:\n");
    // visitedSet.clear();
    // dfs(si, sj);
    // printf("\tReached %ld different states\n", visitedSet.size());
    // printf("\tTook %d steps\n", minSteps);
    //
    // table = aux;
    // printf("BFS:\n");
    // visitedSet.clear();
    // bfs(si, sj);
    // printf("\tReached %ld different states\n", visitedSet.size());
    // printf("\tTook %d steps\n\n", minSteps);

    // table = aux;
    // printf("A* (manhattanDistance):\n");
    // visitedSet.clear();
    // aStar(si, sj, manhattanDistance);
    // printf("\tReached %ld different states\n", visitedSet.size());
    // printf("\tTook %d steps\n\n", minSteps);

    // table = aux;
    // printf("A* (euclideanDistance):\n");
    // visitedSet.clear();
    // aStar(si, sj, euclideanDistance);
    // printf("\tReached %ld different states\n", visitedSet.size());
    // printf("\tTook %d steps\n\n", minSteps);
    // ss = minSteps;

    table = aux;
    if (verbose) printf("A* (new):\n");
    aStar(si, sj, euclideanDistance, 0.01);
    if (verbose) printStatistics();
    ss = minSteps, sss = visitedSet.size();

    table = aux;
    if (verbose) printf("IDA* (euclideanDistance):\n");
    aStar(si, sj, euclideanDistance, 0);
    if (verbose) printStatistics();

    if (minSteps < ss) aa ++; else bb ++;
    if (visitedSet.size() < sss) aaa ++; else bbb ++;
    if (verbose) printf("minSteps: old: %d, new: %d\n", aa, bb);
    if (verbose) printf("states  : old: %d, new: %d\n", aaa, bbb);
  }
  printf("minSteps: old: %d, new: %d\n", aa, bb);
  printf("states  : old: %d, new: %d\n", aaa, bbb);
  
  return(0);
}
