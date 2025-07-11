/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

string s;

void solve() {
    // Trie's solution here
    cin >> s;
    int sizeOfString = s.size();
    int cnt1, cnt2;

    int ok = 0;
    cnt1 = cnt2 = 0;
    for (int i = 0; i < sizeOfString; ++i) {
        if (s[i] == 'A' && s[i + 1] == 'B' && cnt1 == 0) {
            ++cnt1;
            i ++;
            continue;
        }
        if (s[i] == 'B' && s[i + 1] == 'A' && cnt2 == 0 && cnt1) {
            ++cnt2;
            i ++;
            continue;
        }
    }
    if (cnt1 && cnt2) ok = max(ok, 1ll);
    else ok = max(ok, 0ll);
    //cout << cnt1 <<' ' << cnt2 << endl;
    cnt1 = cnt2 = 0;
    for (int i = 0; i < sizeOfString; ++i) {
        if (s[i] == 'B' && s[i + 1] == 'A' && cnt2 == 0) {
            ++cnt2;
            i ++;
            continue;
        }
        if (s[i] == 'A' && s[i + 1] == 'B' && cnt1 == 0 && cnt2) {
            ++cnt1;
            i ++;
            continue;
        }
    }
    if (cnt1 && cnt2) ok = max(ok, 1ll);
    else ok = max(ok, 0ll);
    //cout << cnt1 <<' ' << cnt2 << endl;
    cout << ((ok) ? "YES" : "NO");
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