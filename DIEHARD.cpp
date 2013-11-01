/* 
 * Author: Hakobyan Tigran
 */

#pragma comment(linker, "/STACK:60777216") 
#define printTime(begin, end) printf("Total running time is : %.3lf\n", (double)(end - begin) / (double)CLOCKS_PER_SEC) 


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

int f[maxN][maxN][3];

int go (int h, int a, int last) {
  if(h <= 0 || a <= 0)
    return 0;
  int &ref = f[h][a][last];
  if(ref != -1)
    return ref;
  ref = 0;
  if(last == 0) {
    ref = go(h - 5, a - 10, 1) + 1;
    ref = max(ref, go(h - 20, a + 5, 2) + 1);
  }
  else if(last == 1) {
    ref = go(h + 3, a + 2, 0) + 1;
    ref = max(ref, go(h - 20, a + 5, 2) + 1);
  }
  else if(last == 2) {
    ref = go(h + 3, a + 2, 0) + 1;
    ref = max(ref, go(h - 5, a - 10, 1) + 1);
  }

  return ref;
}

int main () {
#ifdef ALPHA_RAU_PROJECT
  time_t begin = clock();
  IN("input.txt");
  OUT("output.txt");
#endif

  memset(f, -1, sizeof(f));

  int test_case;
  scanf("%d", &test_case);

  while(test_case--) {
    int h, a;
    scanf("%d%d", &h, &a);
    printf("%d\n", max(go(h, a, 0) - 1, max(go(h, a, 1) - 1, go(h, a, 2) - 1)));
  }

#ifdef ALPHA_RAU_PROJECT
  time_t end = clock();
  printTime(begin, end);
#endif
  return 0;
}
