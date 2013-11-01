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

const int maxN = 1000007;

int n, d, l;
char s[maxN];
int f[maxN][2];

void init () {
  scanf("%d%d%d", &n, &l, &d);
  scanf("%s", s);
  for(int i = 0; i < l / 2; ++i)
    swap(s[i], s[l - i - 1]);
  for(int i = l; i <= n + 2; ++i)
    s[i] = '0';
  memset(f, 0, sizeof(f));
}

void solve () {
  f[0][0] = 1;
  for(int i = 0; i < n; ++i) {
    for(int carry = 0; carry < 2; ++carry) {
      if(carry == 0 && s[i] == '0') {
        f[i + 1][0] += f[i][0];
        if(f[i + 1][0] >= d) 
          f[i + 1][0] -= d;
      }
      else if(carry == 0 && s[i] == '1') {
        f[i + 1][0] += f[i][0];
        if(f[i + 1][0] >= d)
          f[i + 1][0] -= d;
        f[i + 1][1] += f[i][0];
        if(f[i + 1][1] >= d)
          f[i + 1][1] -= d;
      }
      else if(carry == 1 && s[i] == '0') {
        f[i + 1][0] += f[i][1];
        if(f[i + 1][0] >= d)
          f[i + 1][0] -= d;
        f[i + 1][1] += f[i][1];
        if(f[i + 1][1] >= d)
          f[i + 1][1] -= d;
      }
      else {
        f[i + 1][1] += f[i][1];
        if(f[i + 1][1] >= d)
          f[i + 1][1] -= d;
      }
    }
  }
  printf("%d\n", f[n][0]);
}

int main () {
  int test_case;

  scanf("%d", &test_case);
  while(test_case--) {
    init();
    solve();
  }
  return 0;
}
