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
int a[10];

void solve() {
    // Trie's solution here
    for (int i = 1; i <= 5; ++i) cin >> a[i];  
    for (int i = 5; i >= 1; --i) {
        if (a[i] == 1) cout << i;
    }
}

#define TASK "test"

signed main()
{
   ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
   solve();
   return 0;
}