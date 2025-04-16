/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e5 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n;
int a[N];

int f[N][35];

bool check(int x) {
    for (int i = 0; i <= 33; ++i) {
        int val = (1ll << i);
        if (val == x) return 1;
    }
    return 0;
}

void solve() {
    // Trie's solution here
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {

    }
    for (int i = 1; i <= n; ++i) {
        for (int cnt = 0; cnt <= 33; ++cnt) {
            int val = (1LL << cnt);
            int cur = a[i];
            int tmp = 0;
            while (!check(cur)) {
                cur /= 2;
                ++tmp;
            }
            while (cur != val) {
                if (cur < val) cur *= 2;
                else cur /= 2;
                ++tmp;
            }
            f[i][cnt] = tmp;
        }
    }
    int res = oo, sum = 0;
    for (int i = 0; i <= 33; ++i) {
        sum = 0;
        for (int j = 1; j <= n; ++j) {
            sum += f[j][i];
        }
        res = min(res, sum);
    }
    cout << res;
}


signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("pow2.inp", "r", stdin);
    freopen("pow2.out", "w", stdout);
    solve();
    return 0;
}