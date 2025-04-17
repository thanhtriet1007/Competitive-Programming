/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, q, m;
vector<int>adj[N];

int par[N], sz[N], idChain[N], headChain[N], pos[N], depth[N];
int curChain, curPos;

void preDfs(int u, int p) {
    ++sz[u];
    for (int &v : adj[u]) {
        if (v == p) continue;
        par[v] = u;
        depth[v] = depth[u] + 1;
        preDfs(v, u);
        sz[u] += sz[v];
    }
}

void decomp(int u, int p) {
    if (headChain[curChain] == 0) {
        headChain[curChain] = u;
    }
    idChain[u] = curChain;
    pos[u] = ++curPos;
    int nxt = 0;
    for (int &v : adj[u]) {
        if (v == p) continue;
        if (nxt == 0 || sz[v] > sz[nxt]) {
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
        if (idChain[u] > idChain[v]) {
            u = par[headChain[idChain[u]]];
        }
        else {
            v = par[headChain[idChain[v]]];
        }
    }
    if (depth[v] < depth[u]) return v;
    else return u;
}

struct IT {
    struct Node {
        int cnt_zero;
        int min_val, max_val;
        int lazy;
    } st[4 * N];
    
    void apply(int id, int l, int r, int val) {
        st[id].min_val += val;
        st[id].max_val += val;
        st[id].lazy += val;
        if (st[id].min_val == 0 && st[id].max_val == 0) {
            st[id].cnt_zero = r - l + 1;
        } else if (st[id].min_val > 0 || st[id].max_val < 0) {
            st[id].cnt_zero = 0;
        }
        // Nếu vẫn còn phần tử 0 và phần tử khác 0 thì ta giữ nguyên cnt_zero
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
}seg;

//each node maintain one edge (like: par -> child)
//node 1 maintain nothing

void update(int u, int v, int val) {
    int lca = getLca(u, v);

    // Cập nhật từ u đến LCA
    while (idChain[lca] != idChain[u]) {
        int cur = pos[headChain[idChain[u]]];
        seg.update(1, 1, n, cur, pos[u], val);
        u = par[headChain[idChain[u]]];
    }

    // Cập nhật từ v đến LCA
    while (idChain[lca] != idChain[v]) {
        int cur = pos[headChain[idChain[v]]];
        seg.update(1, 1, n, cur, pos[v], val);
        v = par[headChain[idChain[v]]];
    }

    // Nếu u và v đã gặp nhau tại LCA, không cần cập nhật lại
    if (u == v) return;

    // Cập nhật đoạn giữa u và v trong cùng một chuỗi nặng
    if (pos[v] < pos[u]) 
        seg.update(1, 1, n, pos[v] + 1, pos[u], val);
    else 
        seg.update(1, 1, n, pos[u] + 1, pos[v], val);
}


vector<ii>importantEdge, normalEdge;
map<ii, bool>markEdge;

void solve() {
    // Trie's solution here
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v, c; cin >> u >> v >> c;
        if (u > v) swap(u, v);
        if (c == 0) {
            importantEdge.push_back({u, v});
        }
        else {
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

    for (int i = 2; i <= n; ++i) {
        seg.update(1,1,n,i,i,0);
    }
    for (auto [u, v] : normalEdge) {
        update(u, v, +1);
    }    
    cin >> q;
    cout << seg.query(1,1,n,2,n) << endl;
    while (q--) {
        int u, v; cin >> u >> v;
        if (u > v) swap(u, v);
        if (markEdge[{u, v}] == 1) {
            update(u, v, -1);
            markEdge[{u, v}] = 0;
        }
        else {
            markEdge[{u, v}] = 1;
            update(u, v, +1);
        }
        cout << seg.query(1,1,n,2,n) << endl;
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
