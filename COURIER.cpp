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

#define clear(dp) memset(dp, -1, sizeof(dp))
#define reset(arr) memset(arr, 0, sizeof(arr))

#define EPS 1e-9
#define PI acos(-1.0)
#define MOD 1000000007
#define IINF 1000000000
#define LINF 6000000000000000000LL

const int MAXN = 100 + 7;

int n, m, z, h, tl;
int s[5], t[5], b[5], l[5];
vector < pair < int, int > > g[MAXN];
int c[MAXN], d[MAXN][MAXN], f[MAXN][1 << 12];

void init () {
  scanf("%d%d%d", &n, &m, &h);
  for(int i = 0; i < m; ++i) {
    int p, q, w;
    scanf("%d%d%d", &p, &q, &w);
    g[p - 1].push_back(mp(q - 1, w));
    g[q - 1].push_back(mp(p - 1, w));
  }
  h--;
  scanf("%d", &z);
  for(int i = 0; i < z; ++i) {
    scanf("%d%d%d", s + i, t + i, b + i);
    s[i] = s[i] - 1;
    t[i] = t[i] - 1;
    l[i] = 0;
    int curr = b[i];
    while(curr) {
      ++l[i];
      curr >>= 1;
    }
  }
}

class Comparator {
public:
  bool operator () (int ind1, int ind2) {
    return c[ind1] < c[ind2];
  }
};

void precalc_dist (int v) {
  for(int i = 0; i < n; ++i) {
    c[i] = IINF;
  }
  c[v] = 0;
  set < int, Comparator > q;
  q.insert(v);
  while(!q.empty()) {
    int u = *q.begin();
    q.erase(u);
    for(vector < pair < int, int > > ::iterator it = g[u].begin(); it != g[u].end(); ++it) {
      int to = it->first;
      int len = it->second;
      if(c[to] > c[u] + len) {
        q.erase(to);
        c[to] = c[u] + len;
        q.insert(to);
      }
    }
  }
  for(int i = 0; i < n; ++i) {
    d[v][i] = c[i];
  }
}

inline int compress () {
  int mask = 0;
  int shift = 0;
  mask |= b[0] << shift; shift += l[0];
  mask |= b[1] << shift; shift += l[1];
  mask |= b[2] << shift; shift += l[2];
  mask |= b[3] << shift; shift += l[3];
  mask |= b[4] << shift; shift += l[4];

  return mask;
}

inline void decompress (int mask) {
  memset(b, 0, sizeof(b));
  b[0] = mask & ((1 << l[0]) - 1); mask >>= l[0];
  b[1] = mask & ((1 << l[1]) - 1); mask >>= l[1];
  b[2] = mask & ((1 << l[2]) - 1); mask >>= l[2];
  b[3] = mask & ((1 << l[3]) - 1); mask >>= l[3];
  b[4] = mask & ((1 << l[4]) - 1); mask >>= l[4];
}

int go (int v, int mask) {
  if(mask == 0) {
    return d[v][h];
  }
  int &ref = f[v][mask];
  if(ref != -1) {
    return ref;
  }
  ref = IINF;
  for(int j = 0; j < z; ++j) {
    decompress(mask);
    if(b[j] == 0) continue;
    b[j]--;
    ref = min(ref, d[v][s[j]] + d[s[j]][t[j]] + go(t[j], compress()));
  }
  return ref;
}

void calc () {
  memset(f, -1, sizeof(f));
  int msk = compress(); tl = 0;
  tl = l[0] + l[1] + l[2] + l[3] + l[4];
  printf("%d\n", go(h, msk));
}

int main () {
  int test_case;
  scanf("%d", &test_case);
  while(test_case--) {
    init();
    for(int i = 0; i < n; ++i) {
      precalc_dist(i);
    }
    calc();
  }
  return 0;
}
