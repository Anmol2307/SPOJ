#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int maxL = 77;
const int maxN = 100 * 1000 + 7;

int n, queries, cnt, a[maxN];
vector < int > tree[maxN << 2];

void build_tree (int root, int tl, int tr) {
    if(tl == tr) {
        tree[root] = vector < int > (1, a[tl]);
    }
    else {
        int tm = (tl + tr) >> 1;
        build_tree(root << 1, tl, tm);
        build_tree((root << 1) | 1, tm + 1, tr);
        tree[root].resize(tr - tl + 1);
        merge(tree[root << 1].begin(), tree[root << 1].end(), tree[(root << 1) | 1].begin(), tree[(root << 1) | 1].end(), tree[root].begin());
    }
}

int curr;
bool found;

int query (int root, int tl, int tr, int l, int r) {
    if(l > r) {
        return 0;
    }
    if(tl == l && tr == r) {
        int lo = 0, hi = tree[root].size() - 1;
        int res = -1;
        while(lo <= hi) {
            int mid = (lo + hi) >> 1;
            if(tree[root][mid] <= curr) {
                res = mid;
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        if(res == -1) {
            return 0;
        }
        if(tree[root][res] == curr) {
            found = true;
        }
        return res + (tree[root][res] < curr ? 1 : 0);
    }
    else {
        int tm = (tl + tr) >> 1;
        return query(root << 1, tl, tm, l, min(r, tm)) + query((root << 1) | 1, tm + 1, tr, max(l, tm + 1), r);
    }
}


int main () {
    scanf("%d%d", &n, &queries);
    for(int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    build_tree(1, 0, n - 1);
    for(int i = 0; i < queries; ++i) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        l--, r--;
        int lo = 0, hi = n - 1;
        while(lo <= hi) {
            int mid = (lo + hi) >> 1;
            curr = tree[1][mid];
            found = false;
            int get_that = query(1, 0, n - 1, l, r);
            if(get_that == k - 1 && found == true) {
                printf("%d\n", curr);
                break;
            }
            else if(get_that > k - 1) {
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }
    }   
    return 0;
}
