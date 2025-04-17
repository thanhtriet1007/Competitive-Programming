#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct Node {
    int cnt_zero;
    int min_val, max_val;
    int lazy;
} st[4 * N];

int a[N];

void build(int id, int l, int r) {
    if (l == r) {
        st[id].min_val = st[id].max_val = a[l];
        st[id].cnt_zero = (a[l] == 0 ? 1 : 0);
        st[id].lazy = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id].lazy = 0;
    st[id].min_val = min(st[id * 2].min_val, st[id * 2 + 1].min_val);
    st[id].max_val = max(st[id * 2].max_val, st[id * 2 + 1].max_val);
    st[id].cnt_zero = st[id * 2].cnt_zero + st[id * 2 + 1].cnt_zero;
}

void apply(int id, int l, int r, int val) {
    st[id].min_val += val;
    st[id].max_val += val;
    st[id].lazy += val;
    if (st[id].min_val == 0 && st[id].max_val == 0) {
        st[id].cnt_zero = r - l + 1;
    } else if (st[id].min_val > 0 || st[id].max_val < 0) {
        st[id].cnt_zero = 0;
    }
    // Nếu vẫn còn phần tử 0 và phần tử khác 0 thì ta giữ nguyên cnt_zero
}

void push(int id, int l, int r) {
    if (st[id].lazy == 0) return;
    int mid = (l + r) / 2;
    apply(id * 2, l, mid, st[id].lazy);
    apply(id * 2 + 1, mid + 1, r, st[id].lazy);
    st[id].lazy = 0;
}

void update(int id, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return;
    if (u <= l && r <= v) {
        apply(id, l, r, val);
        return;
    }
    push(id, l, r);
    int mid = (l + r) / 2;
    update(id * 2, l, mid, u, v, val);
    update(id * 2 + 1, mid + 1, r, u, v, val);
    st[id].min_val = min(st[id * 2].min_val, st[id * 2 + 1].min_val);
    st[id].max_val = max(st[id * 2].max_val, st[id * 2 + 1].max_val);
    st[id].cnt_zero = st[id * 2].cnt_zero + st[id * 2 + 1].cnt_zero;
}

int query(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return st[id].cnt_zero;
    push(id, l, r);
    int mid = (l + r) / 2;
    return query(id * 2, l, mid, u, v) + query(id * 2 + 1, mid + 1, r, u, v);
}

int main() {
    int n = 5;
    a[0] = 0; a[1] = 1; a[2] = 0; a[3] = 2; a[4] = 1;

    //build(1, 0, n - 1);
    for (int i = 0; i <= 4; ++i) {
        update(1,0,n - 1, i,i, 0);
    }

    cout << "Ban đầu: " << query(1, 0, n - 1, 0, 4) << "\n";  // 3 số 0

    update(1, 0, n - 1, 0, 2, 1);  // tăng a[0..2] lên 1

    cout << "Sau khi +1 [0..2]: " << query(1, 0, n - 1, 0, 4) << "\n";  // còn 1 số 0

    update(1, 0, n - 1, 2, 4, -1);  // giảm a[2..4] đi 1

    cout << "Sau khi -1 [2..4]: " << query(1, 0, n - 1, 0, 4) << "\n";  // còn 2 số 0
}
