/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n;

void solve() {
    // Trie's solution here
    cin >> n;
    int cur = n / 6;
    int tmp = n % 6;
    int mi = 0, ma = n * 6;
    mi += cur;
    for (int i = 5; i >= 1; --i) {
        mi += (tmp / i) * (6 - i + 1);
        if (tmp / i != 0) tmp = tmp % i;
    }
    cout << mi << ' ' << ma << endl;
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