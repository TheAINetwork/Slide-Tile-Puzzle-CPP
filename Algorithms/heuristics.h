int weights[10];

double manhattanDistance()
{
  int dist = 0;
  for (int i = 0; i < size; i ++)
    for (int j = 0; j < size; j ++)
    {
      int at = table[i][j] - 1;
      dist += abs(at / size - i) + abs(at % size - j);
    }
  return(dist);
}

double euclideanDistance()
{
  double dist = 0;
  for (int i = 0; i < size; i ++)
    for (int j = 0; j < size; j ++)
    {
      if (table[i][j] == 0) continue;
      int at = table[i][j] - 1;
      dist += sqrt(pow(at / size - i, 2) + pow(at % size - j, 2)); //sqrt
    }
  return(dist);
}

double wrongPieces()
{
  double dist = 0;
  for (int i = 0; i < size; i ++)
    for (int j = 0; j < size; j ++)
      dist += table[i][j] != (i*size + j);
  return(dist);
}

double newHeuristic()
{
  return(euclideanDistance() * manhattanDistance() * wrongPieces());
}
