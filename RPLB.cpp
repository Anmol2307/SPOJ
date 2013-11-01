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

const int maxN = 1000 + 7;

int n, k;
int a[maxN];
bool f[3][maxN];

void init () {
  scanf("%d%d", &n, &k);
  for(int i = 0; i < n; ++i)
    scanf("%d", a + i);
}

void solve () {
  memset(f[0], false, sizeof(f[0]));
  memset(f[1], false, sizeof(f[1]));

  f[0][0] = true;
  int s, t;
  for(int i = 0; i < n; ++i) {
    int first = i % 3;
    int second = (first + 1 == 3 ? 0 : first + 1);
    int third = (second + 1 == 3 ? 0 : second + 1);

    t = third;
    s = second;

    memset(f[third], false, sizeof(f[third]));

    for(int usedSpace = 0; usedSpace  <= k; ++usedSpace) {
      if(f[first][usedSpace]) {
        f[second][usedSpace] = true;
        if(usedSpace + a[i] <= k) {
          f[third][usedSpace + a[i]] = true;
        }
      }
    }
  }

  int ans = -1;

  for(int i = k; i >= 0; --i) {
    if(f[s][i]) {
      ans = max(ans, i);
    }
    if(f[t][i])
      ans = max(ans, i);
  }

  printf("%d\n\n", ans);
}

int main () {
  int test_case;
  
  scanf("%d", &test_case);

  int test_id(0);

  while(test_case--) {

    init();

    printf("Scenario #%d: ", ++test_id);
    solve();
  
  }

  return 0;
}
