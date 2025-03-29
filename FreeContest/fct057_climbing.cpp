/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, m, c;
int a[N];

struct IT {
    ii st[N * 4];

    void build(int id, int l, int r) {
        if (l > r) return;
        if (l == r) { 
            st[id] = {a[l], a[l]};
            return;
        }
        int mid = (l + r) >> 1;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id].first = min(st[id * 2].first, st[id * 2 + 1].first);
        st[id].second = max(st[id * 2].second, st[id * 2 + 1].second);
    }

    ii get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return {oo, -oo};
        if (l >= u && r <= v) {
            return st[id];
        }
        int mid = (l + r) >> 1;
        ii valLeft = get(id * 2, l, mid, u, v);
        ii valRight = get(id * 2 + 1, mid + 1, r, u, v);
        ii res;
        res.first = min(valLeft.first, valRight.first);
        res.second = max(valLeft.second, valRight.second);
        return res;
    }
}seg;

void solve() {
    // Trie's solution here
    cin >> n >> m >> c;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    seg.build(1,1,n);
    vector<int>posAnswer;
    for (int i = 1; i + m - 1 <= n; ++i) {
        auto [mi, ma] = seg.get(1,1,n,i, i + m - 1);
        if (ma - mi <= c) {
            posAnswer.push_back(i);
        }
    }
    if ((int)posAnswer.size() == 0) {
        cout << "NONE";
        return;
    }
    for (int &it : posAnswer) cout << it << endl;
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