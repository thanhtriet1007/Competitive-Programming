/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 6e5 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, q;
char s[N];

struct IT {
    int st[N * 4];

    void update(int id, int l, int r, int pos, int val) {
        if (l > pos || r < pos) return;
        if (l == r) {
            st[id] += val;
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

}segtree[30];

void solve() {
    // Trie's solution here
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int i = 1; i <= n; ++i) {
        int num = (s[i] - 'a') + 1;
        segtree[num].update(1,1,n,i,1);
    }
    cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int pos; char c;
            cin >> pos >> c;
            int num1 = (s[pos] - 'a') + 1;
            int num2 = (c - 'a') + 1;
            segtree[num1].update(1,1,n,pos,-1);
            segtree[num2].update(1,1,n,pos,+1);
            s[pos] = c;
        }
        else {
            int l, r; cin >> l >> r;
            int ans = 0;
            for (int i = 'a'; i <= 'z'; ++i) {
                int num = (i - 'a') + 1;
                ans += (segtree[num].get(1,1,n,l,r) > 0);
            }
            cout << ans << endl;
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