vector<vector<int> > table;
int size, scrambleSteps = 1000;
int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};
set<string> visitedSet;
deque<State> q;
priority_queue<State> pq;
vector<State> successors;
int minSteps = -1;
int inf = 1<<20;

void printTable()
{
  int biggest = log10(size * size) + 1;
  for (int i = 0; i < size; i ++)
    for (int j = 0; j < size; j ++)
      printf("%*d%c", biggest, table[i][j], j < size - 1 ? ' ' : '\n');
}

void printStatistics()
{
  printf("\tReached %ld different states\n", visitedSet.size());
  printf("\tTook %d steps\n\n", minSteps);
}

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

int valid(int i, int j)
{
  return(!(i < 0 || i >= size || j < 0 || j >= size));
}

string stateHash()
{
  string aux = "";
  for (int i = 0; i < size; i ++)
    for (int j = 0; j < size; j ++)
    {
      aux.push_back('0' + table[i][j]);
      if (i != size - 1 || j != size - 1) aux += "|";
    }
  return(aux);
}

void scramble()
{
  for (int i = 0, k = 1; i < size; i ++) for (int j = 0; j < size; j ++, k ++)
    table[i][j] = k;
  table[size - 1][size - 1] = 0;

  int s = scrambleSteps, i = size - 1, j = size - 1;
  while (s --)
  {
    int dir; do dir = rand() % 4; while (!valid(i + dy[dir], j + dx[dir]));
    swap(&table[i][j], &table[i + dy[dir]][j + dx[dir]]);
    i += dy[dir], j += dx[dir];
  }
}

int solved()
{
  for (int i = 0, k = 1; i < size; i ++)
    for (int j = 0; j < size; j ++, k ++)
    {
      if (i == size - 1 && j == size - 1) continue;
      if (table[i][j] != k) return(0);
    }
  return(1);
}
