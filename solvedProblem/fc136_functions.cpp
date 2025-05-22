/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, q;
int a[N];

struct dat {
    int l, r;
}ask[N];

int st[N * 4];

void update(int id, int l, int r, int pos, int val) {
    if (l > pos || r < pos) return;
    if (l == r) {
        st[id] = val;
        return;
    }
    int mid = (l + r) >> 1;
    update(id * 2, l, mid, pos, val);
    update(id * 2 + 1, mid + 1, r, pos, val);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) return 0;
    if (l >= u && r <= v) return st[id];
    int mid = (l + r) >> 1;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void solve() {
    // Trie's solution here
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        update(1,1,n,i,a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        int l, r; cin >> l >> r;
        ask[i] = {l, r};
    }
    cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int pos, val;
            cin >> pos >> val;
            update(1,1,n,pos,val);
        }
        else {
            int l, r; cin >> l >> r;
            int ans = 0;
            for (int i = l; i <= r; ++i) {
                ans += get(1,1,n,ask[i].l,ask[i].r);
            }
            printf("%ld\n", ans);
        }
    }
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