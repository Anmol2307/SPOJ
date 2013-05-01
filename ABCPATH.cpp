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

int n, m;
char a[55][55];
int  d[55][55];

int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

bool valid (int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m;
}

int dfs (int x, int y) {
  if(d[x][y] != -1)
    return d[x][y];
  d[x][y] = 0;
  for(int k = 0; k < 8; ++k) {
    int n_x = x + dx[k];
    int n_y = y + dy[k];
    if(valid(n_x, n_y)) {
      if(a[n_x][n_y] == a[x][y] + 1) {
        d[x][y] = max(d[x][y], 1 + dfs(n_x, n_y));
      }
    }
  }
  return d[x][y];
}

int main () {

#ifndef ONLINE_JUDGE
  IN("/home/tigran/Desktop/Debug/input.txt");
  OUT("/home/tigran/Desktop/Debug/output.txt");
#endif

  int test_id(0);

  while(scanf("%d%d", &n, &m)) {
    if(n == 0 && m == 0)
      break;
    for(int i = 0; i < n; ++i) {
      scanf("%s", a[i]);
    }
    int ans = 0;
    for(int i = 0; i < 55; ++i) {
      for(int j = 0; j < 55; ++j) {
        d[i][j] = -1;
      }
    }
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < m; ++j) {
        if(a[i][j] == 'A' && d[i][j] == -1) {
          ans = max(ans, dfs(i, j));
        }
      }
    }
    printf("Case %d: %d\n", ++test_id, ans + 1);
  }
  return 0;
}
