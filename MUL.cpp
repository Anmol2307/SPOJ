/* 
 * Author: Hakobyan Tigran
 */


struct Complex {
  double a_;
  double b_;
  Complex (double a = .0, double b = .0) :
    a_(a), b_(b) {}
  double real () const { return a_; }
  double imagine () const { return b_; }
  Complex& operator += (double p) { a_ += p; return *this; }
  Complex& operator -= (double p) { a_ -= p; return *this; }
  Complex& operator *= (double p) { a_ *= p; b_ *= p; return *this;}
  Complex& operator /= (double p) { a_ /= p; b_ /= p; return *this;}
  Complex& operator += (Complex &p) { a_ += p.a_; b_ += p.b_; return *this; }
  Complex& operator -= (Complex &p) { a_ -= p.a_; b_ -= p.b_; return *this; }
  Complex operator - (const Complex &p) { return Complex(a_ - p.a_, b_ - p.b_); }
  Complex operator + (const Complex &p) { return Complex(a_ + p.a_, b_ + p.b_); }
  Complex operator * (const Complex &p) { return Complex(a_ * p.a_ - b_ * p.b_, a_ * p.b_ + b_ * p.a_); }
  Complex& operator *= (Complex &p) { double a = a_ * p.a_ - b_ * p.b_; double b = a_ * p.b_ + b_ * p.a_; a_ = a, b_ = b; return *this; }
  Complex& operator /= (Complex &p) { double a = a_, b = b_, c = p.a_, d = p.b_; a_ = (a * c + b * d) / (c * c + d * d); b_ = (b * c - a * d) / (c * c + d * d); return *this; }
};


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
 
const int maxM = 10007;
const int maxN = 32770;
 
int n, m, lg;
int res[maxN];
int b_rv[maxN];
char a[maxM], b[maxM];
Complex v1[maxN], v2[maxN];
 
int rev (int p) {
    int ret = 0;
      for(int i = 0; i < lg; ++i) {
            if(p & (1 << i))
                    ret |= 1 << (lg - i - 1);
              }
        return ret;
}
 
void init_bit_rev () {
    for(int i = 0; i < n; ++i)
          b_rv[rev(i)] = i;
}
 
void init () {
    n = 1;
      lg = 0;
        scanf("%s%s", a, b);
          int s = strlen(a), hs = s / 2;
            int l = strlen(b), hl = l / 2;
              int t = (s > l ? s : l);
                for(int i = 0; i < hs; ++i)
                      swap(a[i], a[s - i - 1]);
                  for(int i = 0; i < hl; ++i)
                        swap(b[i], b[l - i - 1]);
                   
                    while(n < t) {
                          ++lg;
                              n <<= 1;
                                }
                      ++lg;
                        n <<= 1;
                          for(int i = 0; i < n; ++i) {
                                if(i < s) {
                                        v1[i] = Complex(a[i] - '0');
                                            }
                                    else {
                                            v1[i] = Complex(0.0);
                                                }
                                        if(i < l) {
                                                v2[i] = Complex(b[i] - '0');
                                                    }
                                            else {
                                                    v2[i] = Complex(0.0);
                                                        }
                                              }
                            init_bit_rev();
}
 
Complex ww[maxN];

void fft (Complex *v, bool inv) {
   
    for(int i = 0; i < n; ++i)
          if(b_rv[i] < i)
                  swap(v[b_rv[i]], v[i]);
     
      for(int len = 2; len <= n; len <<= 1) {
            double angle = (inv ? -1 : 1) * 2.0 * PI / (double) len;
                Complex wlen(cos(angle), sin(angle));
                int len2 = len >> 1;
                ww[0] = Complex(1.0);
                for(int i = 1; i < len2; ++i)
                  ww[i] = ww[i - 1] * wlen; 
                    for(int i = 0; i < n; i += len) {
                                 Complex T,
                                        *pu = v + i,
                                       *pv = v + i + len2,
                                      *pu_e = v + i + len2,
                                     *pw = ww;
                                for( ; pu != pu_e; ++pu, ++pv, ++pw) {
                                 T = *pv * *pw;
                                *pv = *pu - T;
                               *pu += T;
                                }
                    } 
                      }
       
        if(inv)
              for(int i = 0; i < n; ++i)
                      v[i] /= (double)n;
}
 
void solve () {
    init();
     
      fft(v1, false);
        fft(v2, false);
         
          for(int i = 0; i < n; ++i)
                v1[i] *= v2[i];
           
            fft(v1, true);
             
              for(int i = 0; i < n; ++i)
                    res[i] = (int)(v1[i].real() + 0.5);
               
                int carry = 0;
                 
                  for(int i = 0; i < n; ++i) {
                        res[i] += carry;
                            carry = res[i] / 10;
                                res[i] %= 10;
                                  }
                   
                    int i = n - 1;
                      for( ; i >= 0; --i)
                            if(res[i] != 0)
                                    break;
                        if(i == -1)
                              putchar('0');
                          for( ; i >= 0; --i)
                                printf("%d", res[i]);
                            putchar('\n');
}
 
int main () {

    int test_case;
      scanf("%d", &test_case);
        while(test_case--) {
              solve();
                }
          return 0;
}
