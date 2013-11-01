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

const int maxN = 107;

int n, m, c, z;
int a[maxN][maxN], f[maxN][maxN];
int sc[maxN][maxN], sr[maxN][maxN];

void init () {
  c = 0;
  z = 0;
  memset(a, 0, sizeof(a));
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
     int p, q;
     scanf("%d%d", &p, &q);
     --p; --q;
     if(a[p][q] == 1)
       c += 1;
     else {
       z += 1;
       a[p][q] = 1;
     }
  }
//  puts("***********************");
//  for(int i = 0; i < n; ++i) {
//    for(int j = 0; j < n; ++j) {
//      printf("%d ", a[i][j]);
//    }
//    printf("\n");
//  }
//  puts("***********************");
  sc[0][0] = sr[0][0] = a[0][0];
  for(int i = 1; i < n; ++i) {
    sr[0][i] = sr[0][i - 1] + a[0][i];
    sc[i][0] = sc[i - 1][0] + a[i][0];
  }
  for(int i = 1; i < n; ++i) {
    for(int j = 1; j < n; ++j) {
      sr[i][j] = sr[i][j - 1] + a[i][j];
      sc[i][j] = sc[i - 1][j] + a[i][j];
    }
  }
  for(int i = 0; i < n; ++i) {
    f[0][i] = sr[0][i];
    f[i][0] = sc[i][0];
  }
  for(int i = 1; i < n; ++i) {
    for(int j = 1; j < n; ++j) {
      f[i][j] = f[i - 1][j - 1] + sr[i][j - 1] + sc[i - 1][j] + a[i][j];
    }
  }
}

inline int part_sum (int i, int j) {
  if(i < 0 || i > n || j < 0 || j > n)
    return 0;
  return f[i][j];
}

inline int get_sum (int i1, int j1, int i2, int j2) {
  int ss = f[i2][j2];
  ss -= part_sum(i2, j1 - 1);
  ss -= part_sum(i1 - 1, j2);
  ss += part_sum(i1 - 1, j1 - 1);
  return ss;
}

int naive (int i1, int j1, int i2, int j2) {
  int s = 0;
  for(int i = i1; i <= i2; ++i) {
    for(int j = j1; j <= j2; ++j) {
      s += a[i][j];
    }
  }
  return s;
}

int go (int w, int l) {
  int ret = (int)1e9;
  for(int i = 0; i + l <= n; ++i) {
    for(int j = 0; j + w <= n; ++j) {
      if(i == 1 && j == 1) {
        int oh_i_am_here = 77777;
      }
      int k = get_sum(i, j, i + l - 1, j + w - 1);
      //printf("Query : (%d, %d, %d, %d)\nMine = %d\nNaive = %d\n", i, j, i + l - 1, j + w - 1, k, naive(i, j, i + l - 1, j + w - 1));
      if(ret > z - k)
        ret = z - k;
    }
  }
  return ret;
}

void solve () {
  int ans = (int)1e9;
  for(int i = 1; i * i <= m; ++i) {
    if(m % i == 0) {
      int w = i;
      int l = m / w;
      int curr = go(w, l);
      if(ans > curr)
        ans = curr;
      curr = go(l, w);
      if(ans > curr)
        ans = curr;
    }
  }
  printf("%d\n", ans + c);
}

int main () {
//  int test_case;
//  scanf("%d", &test_case);
//  while(test_case--) {
      init();
      solve();
//  }
  return 0;
}
