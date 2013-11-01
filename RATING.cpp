#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int maxN = 300007;

int n;
int tree[maxN];

struct Triple {
  int a;
  int h;
  int idx;

  Triple () {}
};

void update (int pos, int r) {
  for( ; pos < maxN; pos |= pos + 1)
    tree[pos] += r;
}

int internal_sum (int pos) {
  if(pos < 0)
    return 0;
  int res = 0;
  for( ; pos >= 0; pos = (pos & (pos + 1)) - 1)
    res += tree[pos];
  return res;
}

int sum (int l, int r) {
  return internal_sum(r) - internal_sum(l - 1);
}

Triple a[maxN], b[maxN];
int cnt1[maxN], cnt2[maxN];

bool by_first (Triple A, Triple B) {
  return A.a < B.a;
}

bool by_second (Triple A, Triple B) {
  return A.h < B.h;
}

int main () {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i].a, &a[i].h); a[i].idx = i;
    --a[i].a;
    --a[i].h;
    b[i].a = a[i].a;
    b[i].h = a[i].h;
    b[i].idx = i;
  }
  std::sort(a, a + n, by_first);
  std::memset(tree, 0, sizeof(tree));

  for(int i = 0; i < n; ++i) {
    cnt1[a[i].idx] += sum(0, a[i].h - 1);
    update(a[i].h, 1);
  }
  std::sort(b, b + n, by_second);
  std::memset(tree, 0, sizeof(tree));
  for(int i = 0; i < n; ++i) {
    cnt2[b[i].idx] += sum(0, b[i].a - 1);
    update(b[i].a, 1);
  }

  std::memset(tree, 0, sizeof(tree));
  for(int i = 0; i < n; ) {
    int val = a[i].a;
    int k = i;
    while(i < n && a[i].a == val) ++i;
    cnt3[a[k].idx] += sum(0, a[k].h - 1);
    update(a[k].h, 1);
  }
  for(int i = 0; i < n; ++i)
    printf("%d\n", cnt1[i] + cnt2[i] - cnt3[i]);

  return 0;
}
