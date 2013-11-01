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
#define MOD 5000000
#define IINF 1000000000
#define LINF 6000000000000000000LL

const int maxK = 50 + 5;
const int maxN = 10000 + 7;

struct Pair {
  int first;
  int second;

  Pair () : first(-1), second(-1) {}
  Pair (int first_, int second_) : first(first_), second(second_) {}
};

bool operator < (const Pair &x, const Pair &y) {
  if(x.first != y.first)
    return x.first < y.first;
  return x.second < y.second;
}

int n, k;
int s[maxN];
Pair b[maxN];
int prev_idx[maxN];
int direct_table[maxN];
int tree[maxK][maxN];

bool read () {
  if(scanf("%d%d", &n, &k) == EOF)
    return false;
  for(int i = 0; i < n; ++i) {
    scanf("%d", s + i);
    b[i] = Pair(s[i], i);
  }
  int rank = 0;
  sort(b, b + n);
  for(int i = 0; i < n; ) {
    int value = b[i].first;
    while(i < n && b[i].first == value) {
      s[b[i].second] = rank;
      ++i;
    }
    ++rank;
  }
  memset(direct_table, -1, sizeof(direct_table));
  for(int i = 0; i < n; ++i)
    if(direct_table[s[i]] == -1) prev_idx[i] = -1, direct_table[s[i]] = i;
    else prev_idx[i] = direct_table[s[i]], direct_table[s[i]] = i;
  return true;
}

void solve () {
  memset(tree, 0, sizeof(tree));
  for(int i = 0; i < n; ++i) {
    for(int len = 1; len <= k; ++len) {
      if(len == 1) {
        if(prev_idx[s[i]] == -1)
          update(s[i], 1, tree[1]);
      }
      else {
        if(prev_idx[s[i]] == -1)
          update(s[i], query(s[i] - 1, tree[k - 1]), tree[k]);
        else {
          int l = query(s[i] - 1, tree[k - 1]);

      }
    }
  }
}

int main () {
#ifdef ALPHA_RAU_PROJECT
  time_t begin = clock();
  IN("input.txt");
  OUT("output.txt");
#endif

  while(read())
    solve();

#ifdef ALPHA_RAU_PROJECT
  time_t end = clock();
  printTime(begin, end);
#endif
  return 0;
}
