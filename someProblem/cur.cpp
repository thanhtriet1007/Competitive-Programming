void preDfs(int u, int p) {
    ++sz[u];
    for (int &v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        par[v] = u;
        preDfs(v, u);
        sz[u] += sz[v];
    }
}

void decomp(int u, int p) {
    if (!headChain[curChain]) {
        headChain[curChain] = u;
    }
    int nxt = 0;
    idChain[u] = curChain;
    pos[u] = curPos;
    ++curPos;
    for (int &v : adj[u]) {
        if (v == p) continue;
        if (sz[v] > sz[nxt]) {
            nxt = v;
        }
    }
    if (nxt) decomp(nxt, u);
    for (int &v : adj[u]) {
        if (v == p) continue;
        if (v != nxt) {
            ++curChain;
            decomp(v, u);
        }
    }
}

int getLca(int u, int v) {
    while (idChain[u] != idChain[v]) {
        if (idChain[u] > idChain[v]) {
            u = par[headChain[idChain[u]]];
        }
        else v = par[headChain[idChain[v]]];
    }
    if (depth[u] < depth[v]) return u;
    return v;
}