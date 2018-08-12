int dfsRecursive(int i, int j, int now)
{
  if (i == size - 1 && j == size - 1 && solved())
  {
    minSteps = now;
    return(1);
  }

  for (int k = 0; k < 4; k ++)
    if (valid(i + dy[k], j + dx[k]))
    {
      swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
      string nowStateHash = stateHash();
      if (!visitedSet.count(nowStateHash))
      {
        visitedSet.insert(nowStateHash);
        if (dfsRecursive(i + dy[k], j + dx[k], now + 1)) return(1);
      }
      swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
    }
  return(0);
}
