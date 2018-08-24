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

  n = atoi(argv[1]); int runs = atoi(argv[2]), verbose = atoi(argv[3]); double prevWeight = atof(argv[4]);
  for (int i = 5; i < argc; i ++) weights[i - 5] = atof(argv[i]);
  for (int i = 0; i < n; i ++) table.push_back(vector<int>(n));
  int aa = 0, bb = 0, aaa = 0, bbb = 0, aaaa = 0, bbbb = 0, ss, sss;
  while (runs --)
  {
    scramble();
    if (verbose) printTable();
    vector<vector<int> > aux = table;
    int si, sj;
    for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) if (table[i][j] == 0) si = i, sj = j;

    // table = aux;
    // printf("BFS:\n");
    // visitedSet.clear();
    // bfs(si, sj);
    // printf("\tReached %ld different states\n", visitedSet.size());
    // printf("\tTook %d steps\n\n", minSteps);

    table = aux;
    if (verbose) printf("A* (new):\n");
    aStar(si, sj, newHeuristic, prevWeight);
    if (verbose) printStatistics();
    ss = minSteps, sss = visitedSet.size();

    table = aux;
    if (verbose) printf("A* (euclideanDistance):\n");
    aStar(si, sj, euclideanDistance, 0);
    if (verbose) printStatistics();

    if (minSteps < ss) aa ++; else bb ++;
    if (visitedSet.size() < sss) aaa ++; else bbb ++;
    if (minSteps < ss || visitedSet.size() < sss) aaaa ++; else bbbb ++;
    if (verbose) printf("minSteps: old: %d, new: %d\n", aa, bb);
    if (verbose) printf("states  : old: %d, new: %d\n", aaa, bbb);
    if (verbose) printf("both    : old  %d, new: %d\n", aaaa, bbbb);
  }
  printf("minSteps: old: %d, new: %d\n", aa, bb);
  printf("states  : old: %d, new: %d\n", aaa, bbb);
  printf("both    : old  %d, new: %d\n", aaaa, bbbb);

  return(0);
}
