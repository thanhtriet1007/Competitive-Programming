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

void solve() {
    // Trie's solution here
    cin >> n;
    stack<int>st;
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        //if (!st.empty()) cout << st.top() << endl;
        if ((int)st.size() == 0) {
            st.push(x);
        }
        else {
            if (st.top() + x >= -st.top()) st.push(x);
            else st.pop();
        }
    }
    while ((int)st.size()) {
        res += st.top();
        st.pop(); 
    }
    cout << res;
}

#define TASK "test"

signed main()
{
   ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("sequen.inp", "r", stdin);
    freopen("sequen.out", "w", stdout);
   solve();
   return 0;
}