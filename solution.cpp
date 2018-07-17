#include <bits/stdc++.h>
#include <sys/resource.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

class State
{
  public:
  vector<vector<int> > table;
  int step, blackI, blackJ;
  double heuristic;

  State(vector<vector<int> > t, int bi, int bj, int s, double h)
  {
    table = t, blackI = bi, blackJ = bj, step = s, heuristic = h;
  }

  State(vector<vector<int> > t, int bi, int bj, int s)
  {
    table = t, blackI = bi, blackJ = bj, step = s;
  }

  bool operator()(const State& a, const State& b)
  {
    return(a.heuristic < b.heuristic);
  }

  bool operator<(const State& a) const
  {
    return(heuristic > a.heuristic);
  }
};

int n, sqn;
vector<vector<int> > table;
set<string> visitedSet;
deque<State> q;
priority_queue<State> pq;
int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};
int minSteps = -1, scrambleSteps = 1000;

void printTable()
{
  int biggest = log10(n * n) + 1;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      printf("%*d%c", biggest, table[i][j], j < n - 1 ? ' ' : '\n');
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

int dfsRecursive(int i, int j, int now)
{
  // DEBUG { printf("hash: %s\n", stateHash()); printTable(); }
  if (i == n - 1 && j == n - 1 && solved())
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

void dfs(int i, int j)
{
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

void bfs(int i, int j)
{
  q.push_back(State(table, i, j, 0));
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
          q.push_back(State(table, i + dy[k], j + dx[k], minSteps + 1));
        }
        swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
      }
  }
  while (!q.empty()) q.pop_front();
}

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

double newHeuristic()
{
  double dist = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      if (table[i][j] == 0) continue;
      int at = table[i][j] - 1;
      dist += sqrt(pow(at / n - i, 2) + pow(at % n - j, 2));
    }
  return(dist);
}

void aStar(int i, int j, double (*heuristic)())
{
  pq.push(State(table, i, j, 0, heuristic()));
  while (!pq.empty())
  {
    table = pq.top().table, minSteps = pq.top().step, i = pq.top().blackI, j = pq.top().blackJ;
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
          pq.push(State(table, i + dy[k], j + dx[k], minSteps + 1, heuristic()));
        }
        swap(&table[i][j], &table[i + dy[k]][j + dx[k]]);
      }
  }
  while (!pq.empty()) pq.pop();
}

int main()
{
  rlimit R;
  getrlimit(RLIMIT_STACK, &R);
  R.rlim_cur = R.rlim_max;
  setrlimit(RLIMIT_STACK, &R);
  srand(time(NULL));

  scanf("%d", &n); sqn = 9; int kk = 1;
  for (int i = 0; i < n; i ++) table.push_back(vector<int>(n));
  int aa = 0, bb = 0, ss;
  while (kk)
  {
    scramble();
    printTable();
    vector<vector<int> > aux = table;
    int si, sj;
    for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) if (table[i][j] == 0) si = i, sj = j;

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

    table = aux;
    printf("A* (euclideanDistance):\n");
    visitedSet.clear();
    aStar(si, sj, euclideanDistance);
    printf("\tReached %ld different states\n", visitedSet.size());
    printf("\tTook %d steps\n\n", minSteps);
    ss = minSteps;

    // table = aux;
    // printf("A* (new):\n");
    // visitedSet.clear();
    // aStar(si, sj, newEuclideanDistance);
    // printf("\tReached %ld different states\n", visitedSet.size());
    // printf("\tTook %d steps\n\n", minSteps);
    // if (minSteps < ss) aa ++; else bb ++;
    // printf("old: %d, new: %d\n", bb, aa);
  }
  return(0);
}
