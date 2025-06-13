/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

//Bài toán: cho dãy n phần tử, chọn 1 tập số lượng bất kì sao cho tổng tập đó lớn nhất (dùng backtrack)

int n, a[N];
int x[N]; //x[i]: số (phần tử) thứ i có được chọn hay không?
int ans = -oo;
//neo?

void xuly() {
   int sum = 0;
   for (int i = 1; i <= n; ++i) {
      if (x[i] == 1) {
         sum += a[i];
      } // phần tử thứ i được chọn
   }
   ans = max(ans, sum);
}

//(2^n) * n;

void Back(int k) {
   if (k > n) {
      xuly();
      return;
   }
   for (int i = 0; i <= 1; ++i) {
      x[k] = i;
      //i = 1;
      Back(k + 1);
   }
}

void solve() {
   // Trie's solution here
   cin >> n;
   for (int i = 1; i <= n; ++i) {
      cin >> a[i];
   }
   
   Back(1);
   cout << ans;
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