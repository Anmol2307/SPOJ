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

const int maxK = 26;
const int maxN = 1007;

int n, m;
int f[maxN][maxN];
char a[maxN], b[maxN];
int l[maxK], d[maxK][maxN];

void init () {
  scanf("%s%s", a, b);
  n = strlen(a);
  m = strlen(b);
  memset(l, 0, sizeof(l));
  memset(f, 0, sizeof(f));
}

int lower_bound (int pos, int val) {
  int lo = 0, hi = l[pos] - 1;
  int ans = -1;
  while(lo <= hi) {
    int mid = (lo + hi) >> 1;
    if(d[pos][mid] >= val) {
      ans = d[pos][mid];
      hi = mid - 1;
    }
    else {
      lo = mid + 1;
    }
  }
  return ans;
}

void solve () {
  for(int i=0;i<n;++i){
    if(a[i] <'a'||a[i]>'z'){
      while(true){}
    }
  }
  for(int i=0;i<m;++i){
    if(b[i]<'a'||b[i]>'z') {
      while(true){}
    }
  }
  for(int i = n - 1; i >= 0; --i)
    for(int j = m - 1; j >= 0; --j)
      if(a[i] == b[j])
        f[i][j] = f[i + 1][j + 1] + 1;
      else
        f[i][j] = (f[i][j + 1] > f[i + 1][j] ? f[i][j + 1] : f[i + 1][j]);

  int ans = 0, curr_pos = 0;
  for(int i = 0; i < m; ++i)
    d[b[i] - 'a'][l[b[i] - 'a']++] = i;

  for(int i = 0; i < n; ++i) {
    int fn = lower_bound(a[i] - 'a', curr_pos);
    if(fn == -1) {
      ++ans;
      break;
    }
    if(f[i + 1][curr_pos] == n - i - 1) {
      ++ans;
      curr_pos = fn + 1;
    }
  }
  printf("%d\n", ans);
}

int main () {
  int test_case;
#ifndef ONLINE_JUDGE
  IN("/home/tigran/Desktop/Debug/input.txt");
  OUT("/home/tigran/Desktop/Debug/output.txt");
  scanf("%d", &test_case);
#else
  test_case = 1;
#endif

  while(test_case--) {
    init();
    solve();
  }

  return 0;
}
