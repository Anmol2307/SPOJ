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

const int maxN = 11;

int n;
int f[maxN][1 << maxN];

int go (int pos, int mask) {
  if(pos == n)
    return 1;
  int &ref = f[pos][mask];

  if(ref != -1)
    return ref;

  ref = 0;
  int maxBit = -1;
  for(int i = 0; i < n; ++i)
    if(mask & (1 << i))
      maxBit = i;
  for(int i = 0; i <= maxBit + 1; ++i) {
    ref += go(pos + 1, mask | (1 << i));
  }

  return ref;
}

int main () {
  int test_case;
  scanf("%d", &test_case);

  vector < int > ans(12, -1);

  while(test_case--) {
    scanf("%d", &n);
    if(ans[n] == -1) {
      memset(f, -1, sizeof(f));
      ans[n] = go(0, 0);
    }
    printf("%d\n", ans[n]);
  }

  return 0;
}
