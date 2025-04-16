#include <bits/stdc++.h>

#define fto(i, a, b) for (int i = (int)a; i <= (int)b; ++i)
#define fdto(i, a, b) for (int i = (int)a; i >= (int)b; --i)

#define TEST int TEST; cin >> TEST; while(TEST--)
#define FAST ios::sync_with_stdio(false), cin.tie(nullptr);
#define TIME cerr << "time: " << (float)clock() / CLOCKS_PER_SEC << " secs \n"

#define el "\n"
#define yes cout << "YES\n"
#define no cout << "NO\n"

#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(a) (int)a.size()
#define all(a) (a).begin(), (a).end()
#define rall(a) reverse(all(a))

#define vt vector
#define ii pair<int, int>
#define pll pair<ll, ll>

#define db double
#define ll long long
#define ull unsigned long long
#define int128 __int128
#define int ll

#define maxm (int)()
#define maxn (int)()
const int N = 1e5+1;
using namespace std;
int n;
int a[N];
int par[N],sz[N];
int getPar(int u) {

    if(par[u]==u) return u;
    else return par[u]=getPar(par[u]);

}
void giai() {


    cin >> n;
    int ans = 0;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        par[i]=i;
        sz[i]=a[i];
        ans = max(ans,sz[i]);
    }

    cout << ans << '\n';
    int q;
    cin >> q;
    while(q-->0) {
        int id;
        cin >> id;
        if(id<n) {
            int parId = getPar(id);
            int nextPar = getPar(id+1);

            par[parId]=nextPar;

            sz[nextPar]+=sz[parId];

            ans=max(ans,sz[nextPar]);
        }
        else {
            ans = max(ans,sz[getPar(n)]);
        }

        cout << ans << '\n';
    }


}
signed main() {
#define NAME "river" // Author: 116109112
    freopen(NAME".inp", "r", stdin);
    freopen(NAME".out", "w", stdout);
    giai();
    //TIME;
    return 0;
}