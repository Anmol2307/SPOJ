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
#define IINF 1000000000
#define LINF 6000000000000000000LL

const int MOD = 10007;
const int maxN = 30003;
const int HASH_SIZE = 10007;


int n;
char word[22];
int t[maxN], a[maxN];
int hash_values[maxN];
int hash_table[HASH_SIZE];

int hash_value (const char *s, int len) {
  int h = 0;
  int p = 31;
  for(int i = len - 1; i >= 0; --i) {
    h = s[i] + p * h % MOD;
    if(h >= MOD) {
      h -= MOD;
    }
  }
  if(h >= MOD) {
    printf("I have something wrong in implementation!!!!");
  }

  return h;
}

void init () {
  memset(t, 0, sizeof(t));
  memset(hash_table, -1, sizeof(hash_table));
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) {
    scanf("%s", word);
    hash_values[i] = hash_value(word, strlen(word));
  }

  for(int i = 0; i < n; ++i) {
    scanf("%s", word);
    hash_table[hash_value(word, strlen(word))] = i;
  }

  for(int i = 0; i < n; ++i) {
    a[i] = hash_table[hash_values[i]];
  }
}

void update (int i, int delta) {
  for( ; i < n; i |= i + 1) 
    t[i] += delta;
}

int get (int i) {
  int s = 0;
  if(i < 0)
    return 0;
  for( ; i >= 0; i = (i & (i + 1)) - 1)
    s += t[i];
  return s;
}

void solve () {
  int answer = 0;

  for(int i = 0; i < n; ++i) {
    int dbg = get(a[i] - 1);
    answer += a[i] - dbg;
    update(a[i], 1);
  }

  printf("%d\n", answer);
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
