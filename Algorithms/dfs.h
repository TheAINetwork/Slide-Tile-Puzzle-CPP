void dfs(int i, int j)
{
  visitedSet.clear();
  q.push_front(State(table, i, j, 0));
  while (!q.empty())
  {
    table = q.front().table, minSteps = q.front().step, i = q.front().blackI, j = q.front().blackJ;
    q.pop_front();
    if (solved()) break;

    for (int k = 0; k < 4; k ++)
      if (valid(i + dy[k], j + dx[k]))
      {
        swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
        string nowStateHash = stateHash();
        if (!visitedSet.count(nowStateHash))
        {
          visitedSet.insert(nowStateHash);
          q.push_front(State(table, i + dy[k], j + dx[k], minSteps + 1));
        }
        swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
      }
  }
  while (!q.empty()) q.pop_front();
}
