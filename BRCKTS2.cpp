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

const int MAXN = 350000 + 7;

int n;
int c[MAXN];
int dw[MAXN];
int dh[MAXN];
char a[MAXN];

void dfs (int op_pos, int cl_pos) {
    if(op_pos + 1 == cl_pos) {
        dh[op_pos] = 1;
        dw[op_pos] = 1;
        return ;
    }
    int w = 0, h = -1;
    int pos = op_pos + 1;
    while(pos < cl_pos) {
        dfs(pos, c[pos]);
        w += dw[pos] + 1;
        h = max(h, dh[pos]);
        pos = c[pos] + 1;
    }
    dw[op_pos] = w + 1;
    dh[op_pos] = h + 1;
}

long long go (int op_pos, int cl_pos, int fl) {
    if(op_pos == cl_pos - 1) {
        if(fl) {
            return 1;
        }
        else {
            return -1;
        }
    }
    long long ans = 0;
    if(fl) {
        ans += (long long)dw[op_pos] * (long long)dh[op_pos];
    }
    else {
        ans -= (long long)dw[op_pos] * (long long)dh[op_pos];
    }
    int pos = op_pos + 1;
    while(pos < cl_pos) {
        ans += go(pos, c[pos], fl ^ 1);
        pos = c[pos] + 1;
    }
    return ans;
}

long long solve () {
    memset(c, -1, sizeof(c));
    memset(dw, -1, sizeof(dw));
    memset(dh, -1, sizeof(dh));
    stack < int > br;
    br.push(0);
    for(int i = 1; i < n; ++i) {
        if(a[i] == '(') {
            br.push(i);
        }
        else {
            int k = br.top();
            br.pop();
            c[k] = i;
        }
    }
    int pos = 0;
    while(pos < n) {
        dfs(pos, c[pos]);
        pos = c[pos] + 1;
    }
    long long ans = 0;
    pos = 0;

    while(pos < n) {
        ans += go(pos, c[pos], 1);
        pos = c[pos] + 1;
    }
    return ans;
}

int main () {
    int test_case;
    scanf("%d", &test_case);
    while(test_case--) {
        scanf("%s", a);
        n = strlen(a);
        printf("%lld\n", solve());
    }
    return 0;
}
