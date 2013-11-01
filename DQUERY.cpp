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

struct Event {
  int pos;
  int first;
  int second;
  char eventType;

  Event () : 
    first(-1),
    second(-1),
    eventType('0') {
    }

  Event (int first_, int second_, char eventType_) :
    first(first_),
    second(second_),
    eventType(eventType_) {
    }
};

bool operator < (const Event &first_event, const Event &second_event) {
  if(first_event.second < second_event.second)
    return true;
  if(first_event.second > second_event.second)
    return false;
  if(first_event.eventType == 'N')
    return true;
  if(second_event.eventType == 'N')
    return false;
  return false;
}

const int maxN = 30000 + 7;
const int maxQ = 200000 + 7;
const int maxT = 1000000 + 7;

int n, q;
int tree[maxN];
int table[maxT];
int helper[maxQ];
Event queries[maxN + maxQ];

void update (int i, int delta) {
  for( ; i < n; i = i | (i + 1)) 
    tree[i] += delta;
}

int query (int i) {
  int s = 0;
  for( ; i >= 0; i = (i & (i + 1)) - 1)
    s += tree[i];

  return s;
}

int sum (int i, int j) {
  if(i == 0)
    return query(j);
  return query(j) - query(i - 1);
}

void init () {
#ifdef ALPHA_RAU_PROJECT
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  scanf("%d", &n);
  for(int i = 0; i < n; ++i) {
    int p;
    scanf("%d", &p);
    queries[i].first = p;
    queries[i].second = i;
    queries[i].eventType = 'N';
  }
  scanf("%d", &q);
  for(int i = 0; i < q; ++i) {
    int u, w;
    scanf("%d%d", &u, &w);
    queries[n + i].pos = i;
    queries[n + i].first = u - 1;
    queries[n + i].second = w - 1;
    queries[n + i].eventType = 'Q';
  }

  sort(queries, queries + n + q);
  memset(table, -1, sizeof(table));
}

void solve () {
  for(int i = 0; i < n + q; ++i) {
    if(queries[i].eventType == 'N') {
      if(table[queries[i].first] == -1) {
        update(queries[i].second, 1);
        table[queries[i].first] = queries[i].second;
      }
      else {
        update(table[queries[i].first], -1);
        table[queries[i].first] = queries[i].second;
        update(queries[i].second, 1);
      }
    }
    else {
      helper[queries[i].pos] = sum(queries[i].first, queries[i].second);
    }
  }

  for(int i = 0; i < q; ++i) {
    printf("%d\n", helper[i]);
  }
}

int main () {
  init();
  solve();

  return 0;
}
