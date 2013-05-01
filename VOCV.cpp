#include <cstdio>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;


const int MOD = 10007;
const int MAXN = 100077;

int n;
int f[MAXN][2];
int c[MAXN][2];
vector < int > g[MAXN];

int dfs (int v, int nec, int parent = -1) {
  int &ref = f[v][nec];
  if(ref != -1) {
    return ref;
  }
  ref = 0;

  if(nec == 0) {
    int res = 0;
    int cnt = 1;
    for(vector < int > ::iterator it = g[v].begin(); it != g[v].end(); ++it) {
      if(*it == parent) continue;
      res += dfs(*it, 1, v) + 1;
      cnt += dfs(*it, 0, v);
    }
    ref = min(res, cnt);
  }
  else {
    int res = 0;
    for(vector < int > ::iterator it = g[v].begin(); it != g[v].end(); ++it) {
      if(*it == parent) continue;
      res += dfs(*it, 0, v);
    }
    ref = res;
  }
  return ref;
}

int go (int v, int nec, int parent = -1) {
  int &ref = c[v][nec];
  if(ref != -1) {
    return ref;
  }
  ref = 0;

  if(nec == 0) {
    int res = 0;
    int cnt = 1;
    int t = f[v][nec];
    for(vector < int > ::iterator it = g[v].begin(); it != g[v].end(); ++it) {
      if(*it == parent) continue;
      res += f[*it][1] + 1;
      cnt += f[*it][0];
    }
    if(t == res) {
      int s = 1;
      for(vector < int > ::iterator it = g[v].begin(); it != g[v].end(); ++it) {
        if(*it == parent) continue;
        s = s * go(*it, 1, v) % MOD;
      }
      ref += s;
      if(ref >= MOD) ref -= MOD;
    }
    if(t == cnt) {
      int s = 1;
      for(vector < int > ::iterator it = g[v].begin(); it != g[v].end(); ++it) {
        if(*it == parent) continue;
        s = s * go(*it, 0, v) % MOD;
      }
      ref += s;
      if(ref >= MOD) ref -= MOD;
    }
  }
  else {
    int s = 1;
    for(vector < int > ::iterator it = g[v].begin(); it != g[v].end(); ++it) {
      if(*it == parent) continue;
      s = s * go(*it, 0, v) % MOD;
    }
    ref += s;
  }
  return ref;
}

void init () {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) {
    g[i].clear();
  }
  for(int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
  }
  memset(f, -1, sizeof(f));
  memset(c, -1, sizeof(c));
}

int main () {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int test_case;
  scanf("%d", &test_case);
  while(test_case--){
    init();
    int ans = dfs(0, 0);
    ans = min(ans, dfs(0, 1) + 1);
    printf("%d ", ans);
    int res = 0;
    if(f[0][0] == ans) {
      res += go(0, 0);
    }
    if(f[0][1] + 1 == ans) {
      res += go(0, 1);
    }
    printf("%d\n", res - 1);
  }
  return 0;
}
