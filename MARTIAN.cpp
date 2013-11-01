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

const int maxN = 505;
const int maxM = 505;

int n, m;
int f[maxN][maxM];
int b[maxN][maxM], y[maxN][maxM];
int bs[maxN][maxM], ys[maxN][maxM];

void init () {
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      scanf("%d", y[i] + j);
    }
  }

  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      scanf("%d", b[i] + j);
    }
  }

  for(int i = 0; i < n; ++i) {
    ys[i][0] = y[i][0];
    for(int j = 1; j < m; ++j) {
      ys[i][j] = ys[i][j - 1] + y[i][j];
    }
  }

  for(int j = 0; j < m; ++j) {
    bs[0][j] = b[0][j];
    for(int i = 1; i < n; ++i) {
      bs[i][j] = bs[i - 1][j] + b[i][j];
    }
  }


}

void solve () {
  f[0][0] = max(y[0][0], b[0][0]);

  for(int j = 1; j < m; ++j) {
    f[0][j] = f[0][j - 1] + b[0][j];
    if(f[0][j] < ys[0][j]) {
      f[0][j] = ys[0][j];
    }
  }

  for(int i = 1; i < n; ++i) {
    f[i][0] = f[i - 1][0] + y[i][0];
    if(f[i][0] < bs[i][0]) {
      f[i][0] = bs[i][0];
    }
  }

  for(int i = 1; i < n; ++i) {
    for(int j = 1; j < m; ++j) {
      f[i][j] = f[i][j - 1] + bs[i][j];
      if(f[i][j] < f[i - 1][j] + ys[i][j]) {
        f[i][j] = f[i - 1][j] + ys[i][j];
      }
    }
  }

  printf("%d\n", f[n - 1][m - 1]);
}      

int main () {
  int test_case;
  while(scanf("%d%d", &n, &m) && n + m != 0) {
    init();
    solve();
  }

  return 0;
}
