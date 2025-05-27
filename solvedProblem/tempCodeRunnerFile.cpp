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
int a[N];

int ans = 0;

int F(int cnt, int player) {
    if (cnt < a[1]) {
        if (player == 0) {
            return 1;
        }
        else return 0;
    }
    int cur = 0;
    for (int i = 1; i <= m; ++i) {
        cur |= F(cnt - a[i], 1 - player);
    }
    return cur;
}

void solve() {
    // Trie's solution here
    cin >> n >> m;
    for (int i = 1; i <= m ; ++i) cin >> a[i];
    //thằng chơi trước là 1 -> chủ động -> nếu tồn tại trạng thái nó win thì nó sẽ win 
    if (F(n, 1) == 1) {
        cout << "Marisa";
    }
    else cout << "Reimu";
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