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
map<int, int> cnt;

void solve() {
    // Trie's solution here
    cin >> n;
    vector<int>myvec;
    for (int i = 1; i <= n; ++i) {
        int len; cin >> len; 
        ++cnt[len];
        if (cnt[len] == 2) {
            cnt[len] = 0;
            myvec.push_back(len);
        }
    }
    if ((int)myvec.size() < 2) {
        cout << 0;
        return;
    }
    sort(myvec.begin(), myvec.end());
    int ans = myvec.back();
    myvec.pop_back();
    ans *= myvec.back();
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