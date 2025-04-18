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
int q;

vector<ii>importantEdge, normalEdge;
vector<int>adj[N];

int depth[N];



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
        }
    }
    for (auto [u, v] : importantEdge) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preDfs(1, 0);
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