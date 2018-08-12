vector<State> getSuccessors(int i, int j, double (*heuristic)())
{
  vector<State> sss;
  for (int k = 0; k < 4; k ++)
    if (valid(i + dy[k], j + dx[k]))
    {
      swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
      sss.push_back(State(table, i + dy[k], j + dx[k], minSteps + 1, heuristic()));
      // string nowStateHash = stateHash();
      // if (!visitedSet.count(nowStateHash))
      // {
      //   visitedSet.insert(nowStateHash);
      //   pq.push(State(table, i + dy[k], j + dx[k], minSteps + 1, heuristic()));
      // }
      swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
    }
  sort(sss.begin(), sss.end());
  return(sss);
}

int idaStarSearch(deque<State>& path, int g, int bound, double (*heuristic)())
{
  visitedSet.clear();
  int i = 0, j = 0;
  printf("BEFORE\n"); fflush(stdout);
  if (!q.empty())
  {
    table = q.front().table; minSteps = q.front().step;
    i = q.front().blackI, j = q.front().blackJ;
    q.pop_front();
  }
  int f = g + heuristic();
  if (f > bound) return(f);
  if (solved()) return(-1);
  int minimum = inf;
  successors = getSuccessors(i, j, heuristic);
  printf("AFTER\n"); fflush(stdout);
  for (auto succ: successors)
  {
    table = succ.table;
    string nowStateHash = stateHash();
    if (!visitedSet.count(nowStateHash))
    {
      q.push_front(State(table, succ.blackI, succ.blackJ, minSteps + 1));
      int t = idaStarSearch(q, g + heuristic(), bound, heuristic);
      if (t == -1) return(-1);
      if (t < minimum) minimum = t;
      q.pop_front();
    }
  }
  return(minimum);
}

void idaStar(int i, int j, double (*heuristic)())
{
  int bound = heuristic();
  q.push_front(State(table, i, j, 0));
  while (true)
  {
    printf("calling idaStarSearch (bound: %d):\n", bound);
    visitedSet.clear();
    int t = idaStarSearch(q, 0, bound, heuristic);
    printf("idaStar t: %d\n", t); fflush(stdout);
    // if (!q.empty())
    //   table = q.front().table;
    if (t == -1 || solved()) break;
    // if (t >= inf) continue;
    bound = t;
  }
  while (!q.empty()) q.pop_front();
}
