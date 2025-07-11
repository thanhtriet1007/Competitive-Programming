/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n;

int t[1002][1002], a[1002][1002];
int mx[] = {-1, 0, 0, 1};
int my[] = {0, -1, 1, 0};

bool isValid(int i, int j) {
   return (i > 0 && j > 0 && i <= n && j <= n);
}

int id(int i, int j) {
   return (i - 1) * n + j;
}

int par[N], sz[N];
vector<pair<ii, long double>>listEdge;
int ans = 0;

void init(int total) {
   for (int i = 1; i <= total; ++i) {
      sz[i] = 1;
      par[i] = i;
   }
}

int getPar(int node) {
   if (node == par[node]) return node;
   return par[node] = getPar(par[node]);
}

void unite(int u, int v) {
   u = getPar(u); v = getPar(v);
   if (u == v) return;
   if (sz[u] < sz[v]) swap(u, v);
   par[v] = u;
   sz[u] += sz[v];
   ans = max(ans, sz[u]);
}

void sol(int l, int r) {
   for (int i = l; i <= r; ++i) {
      auto [u, v] = listEdge[i].first;
      unite(u, v);
   }
   for (int i = l; i <= r; ++i) {
      auto [u, v] = listEdge[i].first;
      sz[u] = sz[v] = 1;
      par[u] = u;
      par[v] = v;
   }
}


void solve() {
    // Trie's solution here
   cin >> n;
   for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
      cin >> a[i][j];
   }
   for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
         cin >> t[i][j];
      }
   }
   //a[i][j] + t[i][j] * x = a[u][v] + t[u][v] * x
   //- > (t[i][j] - t[u][v]) * x = a[u][v] - a[i][j];
   //x = (a[u][v] - a[i][j]) / (t[i][j] - t[u][v]);
   for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
         for (int _ = 0; _ < 4; ++_) {
            int newx = i + mx[_];
            int newy = j + my[_];
            if (isValid(newx, newy)) {
               listEdge.push_back({{id(i, j), id(newx, newy)}, (long double)(a[newx][newy] - a[i][j]) * 1.0 / ((t[i][j] - t[newx][newy]) * 1.0)});

            }
         }
      }
   }
   init(n * n);
   sort(listEdge.begin(), listEdge.end());
   int r;
   for (int l = 0; l < (int)listEdge.size(); l = r + 1) {
      r = l;
      while (r + 1 < (int)listEdge.size() && listEdge[r + 1].second == listEdge[l].second) {
         ++r;
      }
      cout << ' ' << l << ' ' << r << ' ' << listEdge[l].second << endl;
      sol(l, r);
   }
   cout << ans;
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