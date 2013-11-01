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

int solve () {
  int n;
  scanf("%d", &n);
  deque < int > dq;
  vector < int > v(n);
  for(int i = 0; i < n; ++i)
    dq.push_back(i);
  int iteration = 1;
  while(dq.empty() == false) {
    for(int it = 0; it < iteration; ++it) {
      int at = dq.front();
      dq.pop_front();
      dq.push_back(at);
    }
    v[dq.front()] = iteration++;
    dq.pop_front();
  }
  for(vector < int > ::iterator it = v.begin(); it != v.end(); ++it)
    printf("%d ", *it);
  puts("");
  return 0;
}


int main () {

  int test_case;
  scanf("%d", &test_case);
  while(test_case--)
    solve();

  return 0;
}
