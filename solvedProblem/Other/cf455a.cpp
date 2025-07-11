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
int a[N], b[N];

int st[N * 4], dp[N];

void update(int id, int l, int r, int pos, int val) { 
    if (l > pos || r < pos) return;
    if (l == r) {
        st[id] = val;
        return;
    }
    int mid = (l + r) >> 1;
    update(id * 2, l, mid, pos, val);
    update(id * 2 + 1, mid + 1, r, pos, val); 
    st[id] = max(st[id * 2], st[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) return 0;
    if (l >= u && r <= v) {
        return st[id];
    }
    int mid = (l + r) >> 1; 
    return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

void solve() {
    // Trie's solution here
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int sumOdd = 0, sumEven = 0; 
    for (int i = 1; i <= n; ++i) {
        b[a[i]] += a[i];
    }
    int ans = 0;
    for (int i = 1; i <= 1e5; ++i) {
        dp[i] = get(1,1,n,1, i - 2) + b[i];
        update(1,1,n,i,dp[i]);
        ans = max(ans, dp[i]);
    }
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