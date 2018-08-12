#include "heuristics.h"

void aStar(int i, int j, double (*heuristic)(), double past)
{
  visitedSet.clear();
  pq.push(State(table, i, j, 0, heuristic()));
  while (!pq.empty())
  {
    table = pq.top().table, minSteps = pq.top().step, i = pq.top().blackI, j = pq.top().blackJ;
    double dist = pq.top().distance;
    pq.pop();
    if (solved()) break;

    for (int k = 0; k < 4; k ++)
      if (valid(i + dy[k], j + dx[k]))
      {
        swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
        string nowStateHash = stateHash();
        if (!visitedSet.count(nowStateHash))
        {
          visitedSet.insert(nowStateHash);
          pq.push(State(table, i + dy[k], j + dx[k], minSteps + 1, dist*past + heuristic()));
        }
        swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
      }
  }
  while (!pq.empty()) pq.pop();
}
