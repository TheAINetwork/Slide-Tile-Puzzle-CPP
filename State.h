#ifndef STATE_H
#define STATE_H

class State
{
  public:
  vector<vector<int> > table;
  int step, blackI, blackJ;
  double distance;

  State(vector<vector<int> > t, int bi, int bj, int s, double d)
  {
    table = t, blackI = bi, blackJ = bj, step = s, distance = d;
  }

  State(vector<vector<int> > t, int bi, int bj, int s)
  {
    table = t, blackI = bi, blackJ = bj, step = s;
  }

  bool operator()(const State& a, const State& b)
  {
    return(a.distance < b.distance);
  }

  bool operator<(const State& a) const
  {
    return(distance > a.distance);
  }
};

#endif
