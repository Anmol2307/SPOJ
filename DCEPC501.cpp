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

#define Min(a, b) (a > b ? b : a)
#define Max(a, b) (a < b ? b : a)

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

const int maxN = 100000 + 7;

int n;
int a[maxN];
long long f[maxN];

void init () {
  for(int i = 0; i <= maxN; ++i)
    f[i] = -LINF;
  scanf("%d", &n);
  f[0] = 0;
  for(int i = 0; i < n; ++i)
    scanf("%d", a + i);
}

void solve () {
  for(int i = 0; i < n; ++i) {
    f[Min(n, i + 2)] = Max(f[Min(n, i + 2)], f[i] + a[i]);
    if(i + 1 < n) {
      f[Min(n, i + 4)] = Max(f[Min(n, i + 4)], f[i] + a[i + 1] + a[i]);
    }
    if(i + 2 < n) {
      f[Min(n, i + 6)] = Max(f[Min(n, i + 6)], f[i] + a[i] + a[i + 1] + a[i + 2]);
    }
  }
  printf("%lld\n", f[n]);
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
