double weights[10];

double manhattanDistance()
{
  int dist = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      int at = table[i][j] - 1;
      dist += abs(at / n - i) + abs(at % n - j);
    }
  return(dist);
}

double euclideanDistance()
{
  double dist = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      if (table[i][j] == 0) continue;
      int at = table[i][j] - 1;
      dist += sqrt(pow(at / n - i, 2) + pow(at % n - j, 2)); //sqrt
    }
  return(dist);
}

double wrongPieces()
{
  double dist = 0;
  for (int i = 0; i < n; i ++)
  {
    int diff = 0;
    for (int j = 0; j < n; j ++)
      diff += table[i][j] != (i*n + j);
    if (diff) dist += n*(i + 1);
    if (diff) break;
  }
  return(dist);
}

double lolPieces()
{
  double dist = 0;
  for (int i = 0; i < n; i ++)
  {
    int diff = 0;
    for (int j = 0; j < n; j ++)
      diff += table[i][j] != (i*n + j);
    if (diff) dist += n;
  }
  return(dist);
}

double newHeuristic()
{
  return(weights[0] * euclideanDistance() + weights[1] * manhattanDistance() + weights[2] * wrongPieces() + 0 * weights[3] * lolPieces());
}
