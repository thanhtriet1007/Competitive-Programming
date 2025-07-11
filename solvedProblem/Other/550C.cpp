/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

#define bit(mask, i) (mask & (1ll << i))
#define on(mask, i) (mask | (1ll << i))
#define off(mask, i) (mask | ~(1ll << i))

string s;

int convert(int i, int j, int k) {
   return i * 100 + j * 10 + k;
}

void solve() {
   // Trie's solution here
   cin >> s; 
   int n = (int)s.size();  
   if ((int)s.size() < 20) {
      for (int mask = 1; mask < (1 << n); ++mask) {
         int num = 0;
         for (int i = 0; i < n; ++i) {
            if (bit(mask, i)) {
               num *= 10;
               num += (s[i] - '0');
            }
         }
         if (num % 8 == 0) {
            cout << "YES" << endl;
            cout << num << endl;
            return;
         }
      }
      cout << "NO";
      return;
   }
   for (int i = 2; i < (int)s.size(); ++i) {
      for (int j = 1; j < i; ++j) {
         for (int k = 0; k < j; ++k) {
             int num = convert(s[k] - '0', s[j] - '0', s[i] - '0');
             //cout << num << endl;
             if (num % 8 == 0) {
               cout << "YES" << endl;
               cout << num;
               return;
             }
         }
      }
   }
   cout << "NO";
}

#define TASK "test"

signed main()
{
   ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
   if (fopen("input.txt", "r")) {
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
   }
   solve();
   return 0;
}