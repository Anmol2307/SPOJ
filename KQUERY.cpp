#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

struct Quadrapule {
  int idx;
  int first;
  int second;
  int third;
  Quadrapule(){}
};

const int maxN = 30001;
const int maxQ = 200001;

int n;
int ans[maxQ];
Quadrapule q[maxN + maxQ];
int tree[maxN + maxQ];

void update (int pos, int delta) {
  for( ; pos < maxN; pos |= pos + 1)
    tree[pos] += delta;
}

int internal_sum (int r) {
  if(r < 0)
    return 0;
  int s = 0;
  for( ; r >= 0; r = (r & (r + 1)) - 1)
    s += tree[r];
  return s;
}

int sum (int i, int j) {
  return internal_sum(j) - internal_sum(i - 1);
}

bool operator < (Quadrapule f, Quadrapule s) {
  int val_f, val_s;
  if(f.third == -1) {
    val_f = f.second;
  }
  else {
    val_f = f.third;
  }
  if(s.third == -1) {
    val_s = s.second;
  }
  else {
    val_s = s.third;
  }

  if(val_f != val_s)
    return val_f < val_s;

  if(f.third == -1)
    return true;
  if(s.third == -1)
    return false;

  return f.first < s.first;
}

int main () {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) {
    scanf("%d", &q[i].second);
    q[i].first = i;
    q[i].third = -1;
  }
  int Q;
  scanf("%d", &Q);
  for(int i = 0; i < Q; ++i) {
    int u, r, k;
    scanf("%d%d%d", &u, &r, &k);
    q[i + n].idx = i;
    q[i + n].first = u - 1;
    q[i + n].second = r - 1;
    q[i + n].third = k;
  }
  n += Q;
  std::sort(q, q + n);
  std::reverse(q, q + n);
  for(int i = 0; i < n; ) {
    int val;
    if(q[i].third == -1)
      val = q[i].second;
    else
      val = q[i].third;
    while(i < n) {
      int val1;
      if(q[i].third == -1)
        val1 = q[i].second;
      else
        val1 = q[i].third;
      if(val != val1)
        break;
      if(q[i].third == -1) {
        update(q[i].first, 1);
      }
      else {
        ans[q[i].idx] = sum(q[i].first, q[i].second);
      }
      ++i;
    }
  }

  for(int i = 0; i < Q; ++i)
    printf("%d\n", ans[i]);

  return 0;
}
