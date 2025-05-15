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
vector<int>adj[N];

bool vis[N];

void bfs(int node, int target) {
    queue<int>q;
    if (vis[node] == 1 || node == target) return;
    vector<int>cur;
    int curNode = node;
    q.push(node);
    vis[node] = 1;
    while ((int)q.size()) {
        int u = q.front();
        q.pop();
        cur.push_back(u);
        vis[u] = 1;
        for (int v : adj[u]) {
            if (vis[v] == 1) continue;
            if (v == target) {
                curNode = u;
                continue;
            }
            //vis[v] = 1;
            q.push(v);
        }
    }
}

void solve() {
    // Trie's solution here
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        bfs(v, u);
    }    
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i] == 0) ++cnt;
    }
    if (cnt == 0) cout << n;
    else cout << cnt;
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