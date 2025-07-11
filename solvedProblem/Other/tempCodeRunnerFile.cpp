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
int numberQuestion;

struct datStructures {
   int sz[N], par[N];
   int xr[N];

   int getPar(int node) {
      if (node == par[node]) return node;
      return par[node] = getPar(par[node]);
   }

   bool unite(int u, int v, int val) {
      u = getPar(u); v = getPar(v);
      if (u == v) {
         return (xr[u] == val);
      }
      if (sz[u] < sz[v]) swap(u, v);
      par[v] = u;
      sz[u] += sz[v];
      (xr[u] ^= xr[v]) ^= val;
      return 1;
   }
}dsu;

int compress[N], cnt;
pair<ii, string>ques[N];

void solve() {
    // Trie's solution here
   cin >> n;
   cin >> numberQuestion;
   for (int i = 1; i <= numberQuestion; ++i) {
      cin >> ques[i].first.first >> ques[i].first.second >> ques[i].second;
      compress[++cnt] = ques[i].first.first;
      compress[++cnt] = ques[i].first.second;
   }
   sort(compress + 1, compress + 1 + cnt);
   for (int i = 1; i <= numberQuestion; ++i) {
      auto &[l, r] = ques[i].first;
      l = lower_bound(compress + 1, compress + 1 + cnt, l - 1) - compress;
      r = lower_bound(compress + 1, compress + 1 + cnt, r) - compress;
   }
   for (int i = 1; i <= numberQuestion; ++i) {
      auto [l, r] = ques[i].first;
      //cout << l << ' ' << r << endl;
      dsu.sz[l] = 1;
      dsu.sz[r] = 1;
      dsu.par[l] = l;
      dsu.par[r] = r;
      dsu.xr[l] = dsu.xr[r] = 0; 
   }
   for (int i = 1; i <= numberQuestion; ++i) {
      auto [l, r] = ques[i].first;
      int val = (ques[i].second == "odd");
      //cout << i <<' ' << val << endl;
      bool check = dsu.unite(l, r, val);
      //cout << dsu.xr[dsu.getPar(1)] << endl;
      if (check == 0) {
         cout << i - 1;
         return;
      }
   }
   cout << numberQuestion;
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