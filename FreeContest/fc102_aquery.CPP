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

void bruteForce() {
    a[0] = oo;
    for (; q > 0; --q) {
        int pos, cnt; cin >> pos >> cnt;
        while (cnt > 0) {
            int l = 1, r = pos, ans = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (a[mid] > a[pos]) {
                    l = mid + 1;
                }
                else {
                    ans = mid;
                    r = mid - 1;
                }
            }
            if (cnt / (pos - ans + 1) == 0) {
                for (int i = ans; i <= pos; ++i) {
                    ++a[i];
                    --cnt;
                    if (cnt == 0) break;
                }
            }
            int cur = min(a[ans - 1] - a[ans], cnt / (pos - ans + 1));
            for (int i = ans; i <= pos; ++i) {
                a[i] += cur;
                cnt -= cur;
                if (cnt == 0) break;
            }
            //cout << cnt << endl;
            //for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
            //cout << endl;
            
        }
    }
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
}

struct IT {
    ii st[N * 4];

    void update(int id, int l, int r, int pos, int val) {
        if (l > pos || r < pos) return;
        if (l == r) {
            st[id].first += val;
            st[id].second = pos;
            return;
        }
        int mid = (l + r) >> 1; 
        update(id * 2, l, mid, pos, val);
        update(id * 2 + 1, mid + 1, r, pos, val);
        if (st[id * 2].first <= st[id * 2 + 1].first) {
            st[id] = st[id * 2];
        }
        else st[id] = st[id * 2 + 1];
    }

    ii get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return {oo, oo};
        if (l >= u && r <= v) {
            return st[id];
        }
        int mid = (l + r) >> 1;
        return min(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }
}seg;

void solved() {
    for (int i = 1; i <= n; ++i) seg.update(1,1,n,i,0);
    for (; q > 0; q--) {
        int pos, cnt; cin >> pos >> cnt;
        auto [val, position] = seg.get(1,1,n,1,pos);
        seg.update(1,1,n,position,1);
    }
    for (int i = 1; i <= n; ++i) cout << seg.get(1,1,n,i,i).first << ' ';
}

void solve() {
    // Trie's solution here
    cin >> n >> q;
    if (n <= 2000) {
        bruteForce();
        return;
    }
    else {
        solved();
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
