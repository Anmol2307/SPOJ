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

const int maxN = 55;
const int maxK = 55;

int N, K, b;
long long f[maxN][maxK];

long long go (int v, int k) {
  long long &ref = f[v][k];
  if(ref != -1) return ref;
  if(k == K) {
    ref = (v == b ? 1 : 0);
    return ref;
  }
  ref = 0;
  int n = v + 1, p = v - 1;
  n %= N;
  p = (p % N + N) % N;
  ref += go(n, k + 1) + go(p, k + 1);
  return ref;
}

int main () {
  int test_case;
#ifndef ONLINE_JUDGE
  IN("/home/tigran/Desktop/Debug/input.txt");
  OUT("/home/tigran/Desktop/Debug/output.txt");
#endif

  while(scanf("%d%d", &N, &K) == 2 && N != -1 && K != -1) {
    int a;
    scanf("%d%d", &a, &b);
    a--; b--;
    memset(f, -1, sizeof(f));
    printf("%lld\n", go(a, 0));
  }

  return 0;
}
