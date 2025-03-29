/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 5e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, k;
int a[N];

int Map[N];

void solve() {
    // Trie's solution here
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int countAns = 0;
    for (int i = 1; i <= n; ++i) {
        if (k - a[i] * a[i] >= 0) countAns += Map[k - a[i] * a[i]];
        ++Map[a[i]];
    }
   
    cout << countAns;
}   

#define TASK "test"

signed main()
{
   ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
//    if (fopen("input.txt", "r")) {
//       freopen("input.txt", "r", stdin);
//       freopen("output.txt", "w", stdout);
//    }
   solve();
   return 0;
}