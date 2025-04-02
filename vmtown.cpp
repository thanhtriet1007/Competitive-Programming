/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, m;

struct dat {
    int u, v, op;
}edge[N];

int par[N], depth[N], sizeOfSubtree[N];
int chainId[N], chainHead[N], pos[N];

int curChain, curPos;

vector<int>adj[N];

void preDfs(int u, int p) {
    sizeOfSubtree[u]++;
    for (int &v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        par[v] = u;
        preDfs(v, u);
        sizeOfSubtree[u] += sizeOfSubtree[v];
    }
}

void hld(int u, int p) {
    if (chainHead[curChain] == 0) {
        chainHead[curChain] = u;
    }

}

void solve() {
    // Trie's solution here
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v, op; cin >> u >> v >> op;
        edge[i] = {u, v, op};
    }
    for (int i = 1; i <= m; ++i) { 
        if (edge[i].op == 0) {
            auto [u, v, w] = edge[i];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    curChain = curPos = 1;
    preDfs(1, 0);
    hld(1, 0);
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