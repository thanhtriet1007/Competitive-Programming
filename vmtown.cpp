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
vector<int>adj[N];

int par[N], sz[N], idChain[N], headChain[N], pos[N], depth[N];
int curChain, curPos;

void preDfs(int u, int p) {
    ++sz[u];
    for (int &v : adj[u]) {
        if (v == p) continue;
        par[v] = u;
        preDfs(v, u);
        depth[v] = depth[u] + 1;
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
    int lz[N * 4], st[N * 4];

    void push(int id, int l, int r) {
        if (lz[id] == 0) return;
        st[id] += lz[id];
        lz[id * 2] += lz[id];
        lz[id * 2 + 1] += lz[id];
        lz[id] = 0;
    }

    void update(int id, int l, int r, int u, int v, int val) {
        push(id, l, r);
        if (l > v || r < u) return;
        if (l >= u && r <= v) {
            lz[id] += val;
            push(id, l, r); 
            return;
        }
        int mid = (l + r) >> 1;
        update(id * 2, l, mid, u, v, val);
        update(id * 2 + 1, mid + 1, r, u, v, val);
        st[id] = max(st[id * 2], st[id * 2 + 1]);
    }

    int get(int id, int l, int r, int u, int v) {
        push(id, l, r);
        if (l > v || r < u) return;
        if (l >= u && r <= v) {
            return st[id];
        }
        int mid = (l + r) >> 1;
        return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }
}seg;

//each node maintain one edge (like: par -> child)
//node 1 maintain nothing

void update(int u, int v) {
    int lca = getLca(u, v);
    while (idChain[lca] != idChain[u]) {
        seg.update(1,1,n, pos[headChain[idChain[u]]] + 1, pos[u]);
        u = par[headChain[idChain[u]]];
    }
    while (idChain )
}

void solve() {
    // Trie's solution here
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preDfs(1, 0);
    decomp(1, 0);
    
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
