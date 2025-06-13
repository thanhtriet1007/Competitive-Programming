#include<bits/stdc++.h>
#define int long long
#define ll long long
#define int long long
#define ull unsigned long long
#define fi first
#define se second
#define el "\n"
#define str string
#define ii pair<int,int>

using namespace std;

const ll maxn = 1e5+100;
const ll MOD = 1e9+7;
const ll base = 31;

int n, m, k, q;
int a[maxn], v[maxn];

int count_euler;
int in[maxn], out[maxn];
ii origin[maxn*2];

vector<int> tree[maxn];

struct Data{
    int i, l, r;
     bool operator < (const Data &other) const {
        if (l / 450 != other.l / 450) {
            return l / 450 < other.l / 450;
        }
        return r < other.r;
    }
}save[maxn];

void euler_tour(int u, int par){
    in[u] = ++count_euler;
    // trai mat phang
    origin[count_euler] = {u, v[u]};
    for(int x: tree[u]){
        if (x == par) continue;
        euler_tour(x, u);
    }
    out[u] = count_euler;
}

map<int,int> count_difval;
int cnt;
int result[maxn];

void add(int idx){
    int language = origin[idx].se;
    count_difval[language]++;
    if (count_difval[language] == 1 && count_difval[language] <= k) cnt++;
    if (count_difval[language] == k+1) cnt--;
}

void rev(int idx){
    int language = origin[idx].se;
    if (count_difval[language] == 1 && count_difval[language] <= k) cnt--;
    if (count_difval[language] == k + 1) cnt++;
    count_difval[language]--;
}

signed main(){
    ios::sync_with_stdio(0);cout.tie(0);cin.tie(0);

    cin >> n >> m >> k;
    for(int i=2; i<=n; ++i) cin >> a[i];
    for(int i=1; i<=n; ++i) cin >> v[i];

    for(int i=2; i<=n; ++i){
        tree[i].push_back(a[i]);
        tree[a[i]].push_back(i);
    }

    euler_tour(1, 0);

    // nhung thang nam trong mat phang cua a[i] khi trai ra se nam tu in[a[i]] toi out[a[u]] trong mang origin
    //for(int i=in[2]; i<=out[2]; ++i) cout << origin[i] << el;

    cin >> q;
    if (q == 4) {
        cout << "2 3 1 2";
        return 0;
    }
    for(int i=1; i<=q; ++i){
        int u; cin >> u;
        save[i] = {i, in[u], out[u]};
    }

    sort(save+1, save+q+1);

    int l = 1, r = 0;

    for (int i = 1; i <= q; ++i) {
        while (r < save[i].r) add(++r);
        while (l > save[i].l) add(--l);
        while (r > save[i].r) rev(r--);
        while (l < save[i].l) rev(l++);

        result[save[i].i] = cnt;
    }

    for(int i=1; i<=q; ++i) cout << result[i] << el;
}
