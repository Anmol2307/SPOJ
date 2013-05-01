/* 
 * Author: Hakobyan Tigran
 */

#pragma comment(linker, "/STACK:60777216") 
#define printTime(begin, end) printf("%.3lf\n", (double)(end - begin) / (double)CLOCKS_PER_SEC) 


#include <string.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <utility>
#include <functional>
#include <complex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <limits>
#include <ctime>
#include <cassert>
#include <valarray>

using namespace std;

#define IN(a) freopen(a, "r", stdin)
#define OUT(a) freopen(a, "w", stdout)

#define mp(a, b) make_pair(a, b)
#define det(a, b, c, d) (a * d - c * b)
#define sbstr(s, i, j) s.substr(i, j - i + 1)

//#define clear(dp) memset(dp, -1, sizeof(dp))
//#define reset(arr) memset(arr, 0, sizeof(arr))

#define EPS 1e-9
#define PI acos(-1.0)
#define MOD 1000000007
#define IINF 1000000000
#define LINF 6000000000000000000LL

struct triple {
  int f;
  int s;
  int t;
  triple (int f_ = 0, int s_ = 0, int t_ = 0) :
    f(f_),
    s(s_),
    t(t_) {

    }
};

const int maxK = 303;
const int maxN = 10007;
  
int k, s, n, t;
triple e[maxK];
int d[maxN], dt[maxN];
vector < pair < int, int > > g[maxN];
vector < pair < int, int > > gt[maxN];

void init () {
  int m;
  scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
  for(int i = 0; i < maxN; ++i) {
    d[i] = IINF;
    dt[i] = IINF;
    g[i].clear();
    gt[i].clear();
  }
  s--;
  t--;
  d[s] = 0;
  dt[t] = 0;
  for(int i = 0; i < m; ++i) {
    int p, q, w;
    scanf("%d%d%d", &p, &q, &w);
    g[p - 1].push_back(mp(q - 1, w));
    gt[q - 1].push_back(mp(p - 1, w));
  }
  for(int i = 0; i < k; ++i) {
    scanf("%d%d%d", &e[i].f, &e[i].s, &e[i].t);
  }
}

class Comparator {
public:
  bool operator () (int ind1, int ind2) {
    return d[ind1] < d[ind2];
  }
};

class ComparatorTranspose {
public:
  bool operator () (int ind1, int ind2) {
    return dt[ind1] < dt[ind2];
  }
};

void calc_right_distance () {
  set < int, Comparator > q;
  q.insert(s);
  while(!q.empty()) {
    int v = *q.begin();
    q.erase(q.begin());
    for(int i = 0; i < g[v].size(); ++i) {
      int to = g[v][i].first;
      int len = g[v][i].second;
      if(d[to] > d[v] + len) {
        q.erase(to);
        d[to] = d[v] + len;
        q.insert(to);
      }
    }
  }
}

void calc_transpose_distance () {
  set < int, ComparatorTranspose > q;
  q.insert(t);
  while(!q.empty()) {
    int v = *q.begin();
    q.erase(q.begin());
    for(int i = 0; i < gt[v].size(); ++i) {
      int to = gt[v][i].first;
      int len = gt[v][i].second;
      if(dt[to] > dt[v] + len) {
        q.erase(to);
        dt[to] = dt[v] + len;
        q.insert(to);
      }
    }
  }
}

void solve () {
  calc_right_distance();
  calc_transpose_distance();

  int ans = d[t];

  for(int i = 0; i < k; ++i) {
    int curr = d[e[i].f - 1];
    curr += dt[e[i].s - 1];
    curr += e[i].t;
    if(curr < ans)
      ans = curr;
    curr = d[e[i].s - 1];
    curr += dt[e[i].f - 1];
    curr += e[i].t;
    if(curr < ans)
      ans = curr;
  }
  printf("%d\n", (ans >= IINF ? -1 : ans));
}

int main () {
  int test_case;
#ifndef ONLINE_JUDGE
  IN("/home/tigran/Desktop/Debug/input.txt");
  OUT("/home/tigran/Desktop/Debug/output.txt");
#endif

  scanf("%d", &test_case);

  while(test_case--) {
    init();
    solve();
  }

  return 0;
}
