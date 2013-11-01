uthor: Hakobyan Tigran
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
#define MOD 100000000
#define IINF 1000000000
#define LINF 6000000000000000000LL

#define my_max(a, b) (a > b ? a : b)
#define my_min(a, b) (a < b ? a : b)

struct Activity {
 int s_;
 int e_;

 Activity (int s = 0, int e = 0) :
       s_(s),
       e_(e) {

       }
 };

bool operator < (const Activity &op1, const Activity &op2) {
    if(op1.e_ < op2.e_)
        return true;
    if(op1.e_ > op2.e_)
        return false;
    return op1.s_ < op2.s_;
}

ostream& operator << (ostream &os, Activity &op) {
    os << "{\n" << "start = " << op.s_ << "\n";
    os << "finish = " << op.e_ << "\n}";
    return os;
}

const int maxN = 100007;

int n;
int f[maxN][3];
Activity a[maxN];

int lower_bound (int val) {
      int res = -1;
      int lo = 0, hi = n - 1;
      while(lo <= hi) {
          int mid = (lo + hi) >> 1;
          if(a[mid].s_ >= val) {
              res = mid;
              hi = mid - 1;
          }
          else {
              lo = mid + 1;
          }
      }
      
      return res;
}

int go (int pos) {
    int &ref = f[pos];
    if(ref != -1)
      return ref;
}

void init () {
  scanf("%d", &n);
  if(n == -1) exit(0);
  for(int i = 0; i < n; ++i)
     scanf("%d%d", &a[i].s_, &a[i].e_);
  sort(a, a + n);
  memset(f, -1, sizeof(f));
}

void solve () {
  
  int ans = go(0);
  ans += n;
  if(ans >= MOD)
     ans -= MOD;
  printf("%.8d\n", ans);
}

int main () {
    int test_case;

    while(true) {
      init();
      solve();
    }
    
    return 0;
}


