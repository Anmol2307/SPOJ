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

const int maxN = 107;
const int maxM = 107;

int n, m;
char a[maxN][maxM];
int  f[maxN][maxM][maxN];

int dx[] = {1, 0};
int dy[] = {0, 1};

void init () {
  scanf("%d%d", &n, &m);
  swap(m, n);
  for(int i = 0; i < n; ++i) {
    scanf("%s", a[i]);
  }

  memset(f, -1, sizeof(f));
}

inline bool valid (int x, int y) {
  if(x < 0 || x >= n || y < 0 || y >= m)
    return false;

  if(a[x][y] == '#')
    return false;

  return true;
}

int go (int i, int j, int k) {

  int &ref = f[i][j][k];

  if(ref != -1) {
    return ref;
  }
  if(i == n - 1 && j == n - 1 && k == n + m) {
    ref = 0;
    if(a[n - 1][m - 1] == '*') {
      ref += 1;
    }

    return ref;
  }

  ref = 0;
  int s = k - i;
  int t = k - j;

  ref += (a[i][s] == '*');
  ref += (a[j][t] == '*');
  
  if(ref == 2) {
    ref -= (i == j && s == t);
  }

  int mmax = 0;

  for(int l = 0; l < 2; ++l) {
    for(int p = 0; p < 2; ++p) {
      int n_x = i + dx[l];
      int n_y = s + dy[l];
      int m_x = j + dx[p];
      int m_y = t + dy[p];

      if(valid(n_x, n_y) && valid(m_x, m_y)) {
        mmax = max(mmax, go(n_x, m_x, k + 1));
      }
    }
  }

  ref += mmax;

  return ref;
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
    printf("%d\n", go(0, 0, 0));
  }
  
  return 0;
}
