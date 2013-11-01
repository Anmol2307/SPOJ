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

const int maxN = 66;
const int maxV = 3222;

struct node {
  int volume;
  int importance;

  node *first;
  node *second;
  node *third;

  node () :
    volume(-1),
    importance(-1),
    first(NULL),
    second(NULL),
    third(NULL) {

    }

  node (int volume_, int importance_, node *first_ = NULL, node *second_ = NULL, node *third_ = NULL) :
    volume(volume_),
    importance(importance_),
    first(first_),
    second(second_),
    third(third_) {

    }

  ~node () {
    delete first;
    delete second;
    delete third;
  }
};

int n;
int max_v;
int p[maxN];
int f[2][maxV];
node tmp[maxN];
node *goods[maxN];

ostream & operator << (ostream &os, node &a) {
  cout << a.volume << " " << a.importance << endl;
}

void init () {
  int k;
  scanf("%d%d", &max_v, &k);
  max_v /= 10;
  for(int i = 0; i < k; ++i) {
    int u;
    scanf("%d%d%d", &tmp[i].volume, &tmp[i].importance, &u);
    tmp[i].volume /= 10;
    p[i] = u - 1;
 //   cout << p[i] << endl;
  }
  n = 0;
  for(int i = 0; i < k; ++i) {
    if(p[i] == -1) {
      goods[n] = new node(tmp[i].volume, tmp[i].importance);
      for(int j = 0; j < k; ++j) {
        if(p[j] == i) {
          if(goods[n]->first == NULL) {
            goods[n]->first = new node(tmp[j].volume, tmp[j].importance);
          }
          else if(goods[n]->second == NULL) {
            goods[n]->second = new node(tmp[j].volume, tmp[j].importance);
          }
          else if(goods[n]->third == NULL) {
            goods[n]->third = new node(tmp[j].volume, tmp[j].importance);
          }
        }
      }n++;
    }
  }
/*
  for(int i = 0; i < n; ++i) {
    cout << "********" << endl;
    cout << *goods[i];
    cout << "1---->";
    if(goods[i]->first != NULL)
      cout << *goods[i]->first;
    cout << "2------->";
    if(goods[i]->second != NULL)
      cout << *goods[i]->second;
    cout << "3-------->";
    if(goods[i]->third != NULL)
      cout << *goods[i]->third;
    cout << "********" << endl;
  }
*/
}

int main () {
//  freopen("/home/tigran/Desktop/Debug/input.txt", "r", stdin);
//  freopen("/home/tigran/Desktop/Debug/output.txt", "w", stdout);
  int test_case;
  scanf("%d", &test_case);
  while(test_case--) {
    init();
    memset(f[0], -1, sizeof(f[0]));
    f[0][0] = 0;
    for(int i = 1; i <= n; ++i) {
      int curr = i & 1;
      int prev = curr ^ 1;
      memset(f[curr], 0, sizeof(f[curr]));
      for(int j = 0; j <= max_v; ++j) {
        if(f[prev][j] > f[curr][j])
          f[curr][j] = f[prev][j];
        if(goods[i - 1]->first == NULL) {
          if(goods[i - 1]->volume <= j) {
            if(f[curr][j] < f[prev][j - goods[i - 1]->volume] + goods[i - 1]->volume * goods[i - 1]->importance)
              f[curr][j] = f[prev][j - goods[i - 1]->volume] + goods[i - 1]->volume * goods[i - 1]->importance;
          }
        }
        else {
         int l = 0;
         int imp[3];
         int vol[3];

         if(goods[i - 1]->first != NULL) {
           imp[l] = goods[i - 1]->first->importance;
           vol[l++] = goods[i - 1]->first->volume;
         }

         if(goods[i - 1]->second != NULL) {
           imp[l] = goods[i - 1]->second->importance;
           vol[l++] = goods[i - 1]->second->volume;
         } 

         if(goods[i - 1]->third != NULL) {
           imp[l] = goods[i - 1]->third->importance;
           vol[l++] = goods[i - 1]->third->volume;
         } 

         for(int mask = 0; mask < (1 << l); ++mask) {
           int v = goods[i - 1]->volume;
           int s = goods[i - 1]->volume * goods[i - 1]->importance;
           
           if(mask & (1 << 0)) {
             v += goods[i - 1]->first->volume;
             s += goods[i - 1]->first->volume * goods[i - 1]->first->importance;
           }

           if(mask & (1 << 1)) {
             v += goods[i - 1]->second->volume;
             s += goods[i - 1]->second->volume * goods[i - 1]->second->importance;
           }

          if(mask & (1 << 2)) {
             v += goods[i - 1]->third->volume;
             s += goods[i - 1]->third->volume * goods[i - 1]->third->importance;
           }

          if(v <= j) {
            if(f[curr][j] <= f[prev][j - v] + s) {
              f[curr][j] = f[prev][j - v] + s;
            }
          }
         }
        } 
      }
    }
    int mmax = 0;
    for(int j = 0; j <= max_v; ++j) {
      mmax = max(mmax, f[n & 1][j]);
    }
    printf("%d\n", mmax * 10);
  }
  return 0;
}
