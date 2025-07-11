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

int a[1002][1002];


int moveX[] = {0, 1, 0, -1};
int moveY[] = {1, 0, -1, 0};


struct dat {
    int nodeFrom, nodeTo, diff;
    
    bool operator < (const dat &other) const {
        return diff < other.diff;
    }
};

int getId(int x, int y) {
    return (x - 1) * n + y;
}

bool isValid(int i, int j) {
    return (i > 0 && j > 0 && i <= n && j <= n);
}

vector<dat>listEdge;

void init() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) { 
            for (int _ = 0; _ < 4; ++_) {
                int newX = i + moveX[_];
                int newY = j + moveY[_];
                if (isValid(newX, newY)) {
                    listEdge.push_back({getId(i, j), getId(newX, newY), abs(a[i][j] - a[newX][newY])});
                }
            }
        }
    }
    sort(listEdge.begin(), listEdge.end());
}

int ans = 0;

struct dataStructure1 {
    int sz[N], par[N];

    int getPar(int node) {
        if (node == par[node]) return node;
        return par[node] = getPar(par[node]);
    }

    void joint(int u, int v) {
        u = getPar(u); v = getPar(v);
        if (u == v) return;
        if (sz[u] < sz[v]) {
            swap(u, v);
        }
        par[v] = u; 
        sz[u] += sz[v];
        ans = max(ans, sz[u]);
    }
}dsu;

void sol(int l, int r) {
    //cout << l << ' ' << r << endl;

    for (int i = l; i <= r; ++i) {
        auto [u, v, w] = listEdge[i];
        //if (w == 3) cout << u << ' ' << v << endl;
        dsu.joint(u, v);
    }
    for (int i = l; i <= r; ++i) {
        auto [u, v, w] = listEdge[i];
        dsu.par[u] = u;
        dsu.par[v] = v;
        dsu.sz[u] = dsu.sz[v] = 1;
    }
}

//? dsu roll back

void solve() {
    // Trie's solution here
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) cin >> a[i][j];
    }
    init();
    
    for (int i = 1; i <= n * n; ++i) {
        dsu.sz[i] = 1;
        dsu.par[i] = i;
    }

    int sz = (int)listEdge.size();

    int r;
    
    for (int l = 0; l < sz; l = r + 1) {
        r = l;
        while (r + 1 < sz && listEdge[r + 1].diff == listEdge[l].diff) {
            ++r;
        }   
        sol(l, r);
        //cout << listEdge[l].diff << ' ' << ans << endl;
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