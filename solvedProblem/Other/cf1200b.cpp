/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl           '\n'
#define int            long long

using namespace        std;

typedef pair<int, int> ii;

const int       N      = 1e6 + 7;
const long long oo     = 1e18 + 7;
const long long MOD    = 1e9 + 7;

int n, m, k;
int a[N];

void solve() {
    // Trie's solution here
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    bool canGo = 1;
    for (int i = 1; i < n; ++i) {
        //cout << m << ' ' << a[i] << ' ' << a[i + 1] << endl;
        if (abs(a[i] - a[i + 1]) <= k) {
            if (a[i] >= a[i + 1] - k) {
                m += a[i] - max(0ll, (a[i + 1] - k));
            }
        }
        else {
            if (a[i] < a[i + 1] - k) {
                int needAdd = (a[i + 1] - k - a[i]);
                if (m >= needAdd) {
                    m -= needAdd;
                }
                else {
                    canGo = 0;
                }
            }
            else {
                m += (a[i] - max(0ll, (a[i + 1] - k)));
            }
        }
    }
    cout << ((canGo) ? "Yes" : "No");
    cout << endl;
}

#define TASK "test"

signed main()
{
   ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
   if (fopen("input.txt", "r")) {
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
   }
   int t; cin >> t; 
   while (t--)
   solve();
   return 0;
}