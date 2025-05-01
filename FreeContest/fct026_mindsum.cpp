/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int k;
vector<ii>adj[N];
int d[N];

void dijkstra(int u) {
    for (int i = 0; i <= k; ++i) {
        d[i] = oo;
    }
    d[u] = 0;
    priority_queue<ii, vector<ii>, greater<ii>>pq; 
    pq.push({0, u});
    while ((int)pq.size()) {
        auto [dNode, node] = pq.top();
        //cout << node << ' ' << dNode << endl;
        pq.pop();
        if (d[node] != dNode) continue;
        for (auto [nextNode, nextWeight] : adj[node]) {
            if (d[node] + nextWeight < d[nextNode]) {
                d[nextNode] = dNode + nextWeight;
                pq.push({d[nextNode], nextNode});
            }
        }
    }
}

void solve() {
    // Trie's solution here
    cin >> k;
    for (int i = 0; i < k; ++i) {
        for (int d = 0; d <= 9; ++d) {
            adj[i].push_back({(i * 10 + d) % k, d});
        }
    }
    //node k is fake node
    for (int d = 1; d <= 9; ++d) {
        adj[k].push_back({d, d});
    }
    dijkstra(k);
    cout << d[0];
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