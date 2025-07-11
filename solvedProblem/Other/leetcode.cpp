/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl '\n'
#define int long long

using namespace std;

typedef pair<int, int> ii;

const int N = 1e6 + 7;
const long long oo = 1e18 + 7;
const long long MOD = 1e9 + 7;

int n, limit;
int f[N], g[N], dp[N];

void solve()
{
    // Trie's solution here
    cin >> n >> limit;
    for (int i = 0; i <= n; ++i)
    {
        f[i] = i + 1;
        if (i > limit)
        {
            g[i] += (i - limit);
            g[i] += max(0ll, min(limit, i - limit - 1) + 1);
        }
    }
    int cnt = 0;
    for (int i = 0; i <= n; ++i)
    {
        //cout << i << ' ';
       // cout << f[i] << ' ' << g[i] << endl;
        dp[i] = f[i] - g[i];
        //cout << dp[i] << endl;
    }
    for (int i = 0; i <= n; ++i) {
        if (n - i > limit) continue;
        cnt += dp[i];
    }
    cout << cnt;
}

#define TASK "test"

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    if (fopen("input.txt", "r"))
    {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    solve();
    return 0;
}