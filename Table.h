vector<vector<int> > table;
int n, scrambleSteps = 1000;
int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};
set<string> visitedSet;
deque<State> q;
priority_queue<State> pq;
vector<State> successors;
int minSteps = -1;
int inf = 1<<20;

void printTable()
{
  int biggest = log10(n * n) + 1;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      printf("%*d%c", biggest, table[i][j], j < n - 1 ? ' ' : '\n');
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
  return(!(i < 0 || i >= n || j < 0 || j >= n));
}

string stateHash()
{
  string aux = "";
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      aux.push_back('0' + table[i][j]);
      if (i != n - 1 || j != n - 1) aux += "|";
    }
  return(aux);
}

void scramble()
{
  for (int i = 0, k = 1; i < n; i ++) for (int j = 0; j < n; j ++, k ++)
    table[i][j] = k;
  table[n - 1][n - 1] = 0;

  int s = scrambleSteps, i = n - 1, j = n - 1;
  while (s --)
  {
    int dir; do dir = rand() % 4; while (!valid(i + dy[dir], j + dx[dir]));
    swap(&table[i][j], &table[i + dy[dir]][j + dx[dir]]);
    i += dy[dir], j += dx[dir];
  }
}

int solved()
{
  for (int i = 0, k = 1; i < n; i ++)
    for (int j = 0; j < n; j ++, k ++)
    {
      if (i == n - 1 && j == n - 1) continue;
      if (table[i][j] != k) return(0);
    }
  return(1);
}
