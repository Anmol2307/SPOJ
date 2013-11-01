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

const int maxM = 320;
const int maxN = 100009;

int n, Q;
int block_size;
long long a[maxN];
long long d[maxM];

void update (int left, int right, int value) {
  int l_block_number = left / block_size;
  int r_block_number = right / block_size;
  if(l_block_number == r_block_number) {
    d[l_block_number] += (long long)(right - left + 1) * (long long)value;
    for(int j = left; j <= right; ++j) {
      a[j] += value;
    }
  }
  else {
    for(int j = left; j <= block_size * (l_block_number + 1) - 1; ++j) {
      a[j] += value;
      d[l_block_number] += value;
    }
    for(int j = l_block_number + 1; j <= r_block_number - 1; ++j) {
      d[j] += (long long)value * (long long)block_size;
    }
    for(int j = r_block_number * block_size; j <= right; ++j) {
      a[j] += value;
      d[r_block_number] += value;
    }
  }
}

long long get(int left, int right) {
 long long r = 0;
 int l_block_number = left / block_size;
 int r_block_number = right / block_size;
 if(l_block_number == r_block_number) {
   for(int j = left; j <= right; ++j) {
     r += a[j];
   } 
 } 
 else {
   for(int j = left; j <= block_size * (l_block_number + 1) - 1; ++j) {
     r += a[j];
   } 
   for(int j = l_block_number + 1; j <= r_block_number - 1; ++j) {
     r += d[j];
   } 
   for(int j = r_block_number * block_size; j <= right; ++j) {
     r += a[j];
   } 
 } 

 return r;
}

int main () {
  int test_case;
  scanf("%d", &test_case);
  while(test_case--) {
    scanf("%d%d", &n, &Q);
    block_size = sqrt(n);
    memset(a, 0, sizeof(a));
    memset(d, 0, sizeof(d));
    for(int i = 0; i < Q; ++i) {
    int command_type, p, q, v;
    scanf("%d", &command_type);
    if(command_type == 0) {
      scanf("%d%d%d", &p, &q, &v);
      update(p - 1 , q - 1, v);
    }
    else {
      scanf("%d%d", &p, &q);
      printf("%lld\n", get(p - 1, q - 1));
    }
    }
  }

  return 0;
}
