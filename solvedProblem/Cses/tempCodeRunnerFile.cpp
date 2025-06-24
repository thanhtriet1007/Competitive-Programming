/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, m, k;
int a[N], b[N];

void solve() {
    // Trie's solution here
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];

    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + m);
    int i = 1, j = 1, cnt = 0;
    while (i <= n) {
        if (abs(b[j] - a[i]) <= k) {
            ++i;
            ++j;
            ++cnt;
            continue;
        }
        if (b[j] < a[i] - k) {
            ++j;
        }
        else if (b[j] > a[i] + k) {
            ++i;
        }
    }
    cout << cnt;
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