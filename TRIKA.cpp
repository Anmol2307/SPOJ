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

#define Clear(dp) memset(dp, -1, sizeof(dp))
#define reset(arr) memset(arr, 0, sizeof(arr))

#define EPS 1e-9
#define PI acos(-1.0)
#define MOD 1000000007
#define IINF 1000000000
#define LINF 6000000000000000000LL

int n, m;
int d[3333][3333][2];
vector < int > g[3333];

int dfs (int a, int b, int turn) {
    int &ref = d[a][b][turn];
    if(ref != -1) {
        return ref;
    }
    if(a == b) {
        return ref = 0;
    }
    if(turn == 1) {
        ref = 0;
        for(int i = 0; i < g[a].size(); ++i) {
            int to = g[a][i];
            ref = max(ref, 1 + dfs(to, b, turn ^ 1));
        }
    }
    else {
        ref = IINF;
        for(int i = 0; i < g[b].size(); ++i) {
            int to = g[b][i];
            ref = min(ref, 1 + dfs(a, to, turn ^ 1));
        }
    }
    return ref;
}

int main () {
    int test_case;
    scanf("%d", &test_case);
    while(test_case--) {
        for(int i = 0; i < n; ++i) {
            g[i].clear();
        }
        int a, b;
        scanf("%d%d%d%d", &n, &m, &a, &b);
        a--;
        b--;
        for(int i = 0; i < m; ++i) {
            int p, q;
            scanf("%d%d", &p, &q);
            g[p - 1].push_back(q - 1);
            g[q - 1].push_back(p - 1);
        }
        memset(d, -1, sizeof(d));
        int ans = dfs(a, b, 1);
        if(ans >= IINF) {
            puts("No");
        }
        else {
            printf("%d\n", ans);
        }
    }
    return 0;
}
