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

const int maxN = 202;
const int mod = 100000;

int n;
bool th;
char s[maxN];
int f[maxN][maxN];

void init () {
  th = false;
  scanf("%d%s", &n, s);
  memset(f, -1, sizeof(f)); 
}

inline int get_ways (int b, int e) { 
  if(s[b] == '(' && (s[e] == ')' || s[e] == '?'))
    return 1;
  else if(s[b] == '[' && (s[e] == ']' || s[e] == '?'))
    return 1;
  else if(s[b] == '{' && (s[e] == '}' || s[e] == '?'))
    return 1;
  else if(s[b] == '?' && (s[e] == '}' || s[e] == ']' || s[e] == ')'))
    return 1;
  else if(s[b] == '?' && s[e] == '?')
    return 3;
  else 
    return 0;
}

int go (int b, int e) {
  if(b > e)
    return 1;
  if(b == e)
    return 0;
  int &ref = f[b][e];
  if(ref != -1)
    return ref;
  ref = 0;
  for(int k = b + 1; k <= e; k += 2) {
    int w = get_ways(b, k);
    if(w) {
      long long ss = w * go(b + 1, k - 1);
      ss *= go(k + 1, e);
      ref += ss % mod;
      if(ref >= mod) {
        th = true;
        ref %= mod;
      }
    }
  }
  return ref;
}

int main () {
  int test_case;
#ifndef ONLINE_JUDGE
  scanf("%d", &test_case);
#else
  test_case = 1;
#endif

  while(test_case--) {
    init();
    printf((!th ? "%d\n" : "%.5d\n"), go(0, n - 1));
  }
  return 0;
}
