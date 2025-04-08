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

void solve() {
    // Trie's solution here
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preDfs(i
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