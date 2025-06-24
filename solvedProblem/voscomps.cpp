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
int a[N];

multiset<int>s;

void solve() {
    // Trie's solution here
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    for (int i = 1; i <= n; ++i) {
        if (!(int)s.size()) {
            s.insert(a[i]);
        }
        else {
            auto it = s.lower_bound(a[i] + 1);
            if (it != s.end()) {
                s.erase(it);
            }
            s.insert(a[i]);
        }
    }
    cout << sz(s);
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