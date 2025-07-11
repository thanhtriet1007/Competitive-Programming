/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, m;
int a[N];

int dp[N];

int ans = 0;

int F(int cnt) {
    //cout << cnt << ' ' << player << endl;
    if (cnt <= 0) return 0;
    if (dp[cnt] != -1) return dp[cnt];
    int &res = dp[cnt];
    for (int i = 1; i <= m; ++i) {
        if (cnt >= a[i] && F(cnt - a[i]) == 0) return dp[cnt] = 1;
    }
    return dp[cnt] = 0;
}

void solve() {
    // Trie's solution here
    cin >> n >> m;
    for (int i = 1; i <= m ; ++i) cin >> a[i];
    memset(dp, -1, sizeof(dp));
    if (F(n) == 1) cout << "Marisa";
    else cout << "Reimu";
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