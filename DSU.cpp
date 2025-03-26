#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 1;

struct DSU {
    int par[N], sz[N];

    void init(int number) {
        for (int i = 1; i <= number; ++i) {
            par[i] = i; sz[i] = 1;
        }
    }

    int get(int node) {
        if (par[node] == node) return node;
        return par[node] = get(par[node]);
    } 

    void unite(int u, int v) {
        u = get(u), v = get(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
    }
};