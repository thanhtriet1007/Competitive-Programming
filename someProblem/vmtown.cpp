#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

typedef pair<int, int> ii;

const int N = 1e6 + 7;

int n, q, m;
vector<int> adj[N];

int par[N], sz[N], idChain[N], headChain[N], pos[N], depth[N];
int curChain = 1, curPos = 1;

void preDfs(int u, int p) {
    ++sz[u];
    for (int &v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        par[v] = u;
        preDfs(v, u);
        sz[u] += sz[v];
    }
}

void decomp(int u, int p) {
    if (!headChain[curChain]) {
        headChain[curChain] = u;
    }
    int nxt = 0;
    idChain[u] = curChain;
    pos[u] = curPos++;
    for (int &v : adj[u]) {
        if (v == p) continue;
        if (sz[v] > sz[nxt]) {
            nxt = v;
        }
    }
    if (nxt) decomp(nxt, u);
    for (int &v : adj[u]) {
        if (v == p || v == nxt) continue;
        ++curChain;
        decomp(v, u);
    }
}

int getLca(int u, int v) {
    while (idChain[u] != idChain[v]) {
        if (depth[headChain[idChain[u]]] < depth[headChain[idChain[v]]])
            swap(u, v);
        u = par[headChain[idChain[u]]];
    }
    return depth[u] < depth[v] ? u : v;
}

struct IT {
    struct Node {
        int cnt_zero = 0;
        int min_val = 0, max_val = 0;
        int lazy = 0;
    } st[4 * N];

    void apply(int id, int l, int r, int val) {
        st[id].min_val += val;
        st[id].max_val += val;
        st[id].lazy += val;
        if (st[id].min_val == 0 && st[id].max_val == 0)
            st[id].cnt_zero = r - l + 1;
        else if (st[id].min_val > 0 || st[id].max_val < 0)
            st[id].cnt_zero = 0;
    }

    void push(int id, int l, int r) {
        if (st[id].lazy == 0) return;
        int mid = (l + r) / 2;
        apply(id * 2, l, mid, st[id].lazy);
        apply(id * 2 + 1, mid + 1, r, st[id].lazy);
        st[id].lazy = 0;
    }

    void update(int id, int l, int r, int u, int v, int val) {
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            apply(id, l, r, val);
            return;
        }
        push(id, l, r);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, u, v, val);
        update(id * 2 + 1, mid + 1, r, u, v, val);
        st[id].min_val = min(st[id * 2].min_val, st[id * 2 + 1].min_val);
        st[id].max_val = max(st[id * 2].max_val, st[id * 2 + 1].max_val);
        st[id].cnt_zero = st[id * 2].cnt_zero + st[id * 2 + 1].cnt_zero;
    }

    int query(int id, int l, int r, int u, int v) {
        if (v < l || r < u) return 0;
        if (u <= l && r <= v) return st[id].cnt_zero;
        push(id, l, r);
        int mid = (l + r) / 2;
        return query(id * 2, l, mid, u, v) + query(id * 2 + 1, mid + 1, r, u, v);
    }
} seg;

void update(int u, int v, int val) {
    int lca = getLca(u, v);

    // Từ u đến lca
    while (idChain[u] != idChain[lca]) {
        int top = headChain[idChain[u]];
        seg.update(1, 1, n, pos[top], pos[u], val);
        u = par[top];
    }
    if (u != lca) seg.update(1, 1, n, pos[lca] + 1, pos[u], val);

    // Từ v đến lca
    while (idChain[v] != idChain[lca]) {
        int top = headChain[idChain[v]];
        seg.update(1, 1, n, pos[top], pos[v], val);
        v = par[top];
    }
    if (v != lca) seg.update(1, 1, n, pos[lca] + 1, pos[v], val);
}

vector<ii> importantEdge, normalEdge;
map<ii, bool> markEdge;

int count_bridges() {
    // bỏ node 1 vì nó không đại diện cho cạnh nào
    return seg.query(1, 1, n, 1, n) - seg.query(1, 1, n, pos[1], pos[1]);
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v, c; cin >> u >> v >> c;
        if (u > v) swap(u, v);
        if (c == 0) {
            importantEdge.push_back({u, v});
        } else {
            normalEdge.push_back({u, v});
            markEdge[{u, v}] = 1;
        }
    }

    for (auto [u, v] : importantEdge) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    preDfs(1, 0);
    decomp(1, 0);

    // Chỉ update từ node 2 trở đi
    for (int i = 2; i <= n; ++i) {
        seg.update(1, 1, n, pos[i], pos[i], 0);
    }

    for (auto [u, v] : normalEdge) {
        update(u, v, +1);
    }

    cin >> q;
    cout << count_bridges() << endl;
    while (q--) {
        int u, v; cin >> u >> v;
        if (u > v) swap(u, v);
        if (markEdge[{u, v}] == 1) {
            update(u, v, -1);
            markEdge[{u, v}] = 0;
        } else {
            markEdge[{u, v}] = 1;
            update(u, v, +1);
        }
        cout << count_bridges() << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
