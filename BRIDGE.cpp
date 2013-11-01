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

const int maxN = 1003;

struct pr {
  int first;
  int second;

  pr () :
    first(0),
    second(0) {
    }

  pr(int first_, int second_) :
    first(first_),
    second(second_) {
    }
};

bool operator < (const pr &ac, const pr &bc) {
  if(ac.first < bc.first)
    return true;
  if(ac.first > bc.first)
    return false;
  return ac.second < bc.second;
}

int n;
pr a[maxN];
int f[maxN];

void init() {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) scanf("%d", &a[i].first);
  for(int i = 0; i < n; ++i) scanf("%d", &a[i].second);
  sort(a, a + n);
  for(int i = 0; i < n; ++i)
    f[i] = 1;
}

int main () {
  int test_case;
  scanf("%d", &test_case);
  while(test_case--) {
    init();
    int answer = -1;
    for(int i = 1; i < n; ++i) {
      int mmax = 0;
      for(int j = 0; j < i; ++j) {
        if(a[j].second <= a[i].second)
          mmax = max(mmax, f[j]);
      }
      f[i] = mmax + 1;
      answer = max(answer, f[i]);
    }
    printf("%d\n", answer);
  }
  return 0;
}
