/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, k; 
int a[N], f[N], g[N], s[N];

int compress[N], cloneS[N];

ii st[N * 4];

ii cp(ii a, ii b) {
   ii c;
   c.first = min(a.first, b.first);
   c.second = max(a.second, b.second);
   return c;
}

void update(int id, int l, int r, int pos, ii val) {
   if (l > pos || r < pos) return;
   if (l == r) {
      st[id] = val;
      return;
   }
   int mid = (l + r) >> 1;
   update(id * 2, l, mid, pos, val);
   update(id * 2 + 1, mid + 1, r, pos, val);
   st[id] = cp(st[id * 2], st[id * 2 + 1]);
}

ii get(int id, int l, int r, int u, int v) {
   if (l > v || r < u) return {oo, -oo};
   if (l >= u && r <= v) {
      return st[id];
   }
   int mid = (l + r) >> 1;
   return cp(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

bool check(int maximum) {
   int ma = *max_element(s, s + 1 + n);
   for (int i = 0; i <= n; ++i) {
      update(1,0,n,i,{oo, -oo});
      //f[i] = oo; g[i] = -oo;
   }
   update(1,0,n,s[0],{0, 0});
   //cout << get(1,0,n,s[0], s[0]).first << endl;
   for (int i = 1; i <= n; ++i) {
      int prevPos = lower_bound(compress, compress + 1 + n, cloneS[i] - maximum) - compress;
      ii curPair = get(1,0,n,prevPos,ma);
      //cout << curPair.first << ' ' << curPair.second << endl;
      f[i] = curPair.first + 1;
      g[i] = curPair.second + 1;
      update(1,0,n,s[i],{curPair.first + 1, curPair.second + 1});
   }
   return (f[n] <= k && k <= g[n]);
}

void solve() {
   // Trie's solution here
   cin >> n >> k;
   for (int i = 1; i <= n; ++i) cin >> a[i];
   for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i]; 
   
   for (int i = 1; i <= n; ++i) {
      compress[i] = s[i];
      cloneS[i] = s[i];
   }
   sort(compress, compress + 1 + n);

   for (int i = 0; i <= n; ++i) {
      s[i] = lower_bound(compress, compress + 1 + n, s[i]) - compress;
      //cout << s[i] <<' ';
   }

   
   int l = -1e9, r = 1e9, ans = 0;
   while (l <= r) {
      int mid = (l + r) >> 1;
      if (check(mid)) {
         ans = mid;
         r = mid - 1;
      }
      else l = mid + 1;
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