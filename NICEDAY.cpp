#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

struct Triple {
  int a;
  int b;
  int c;
  Triple () :
    a(0),
    b(0), 
    c(0) {
    }
};

bool comparator (Triple x, Triple y) {
  return x.a > y.a;
}

const int maxN = 100000 + 7;

int n;
int tree[maxN];
Triple results[maxN];

#define max(a, b) (a > b ? a : b)

void update (int pos, int delta) {
  for( ; pos < n; ++pos)
    tree[pos] = max(tree[pos], delta);
}

int query (int pos) {
  int ans = -1;
  for( ; pos >= 0; pos = (pos & (pos + 1)) - 1)
    ans = max(tree[pos], ans);
  return ans;
}

int main () {
  int test_case;
  scanf("%d", &test_case);
  while(test_case--) {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
      scanf("%d%d%d", &results[i].a, &results[i].b, &results[i].c);
      --results[i].a; --results[i].b; --results[i].c;
      results[i].b = n - results[i].b - 1;
    }
    std::memset(tree, -1, sizeof(tree));
    std::sort(results, results + n, comparator);
    int answer = 0;
    for(int i = 0; i < n; ++i) {
      if(query(results[i].b - 1) > results[i].c)
        ++answer;
      update(results[i].b, results[i].c);
    }
    printf("%d\n", n - answer);
  }

  return 0;
}
