#include <bits/stdc++.h>
#define int long long
using namespace std;
string s;
multiset<int,greater<int>> res;
signed main(){
    ios::sync_with_stdio(false); cin.tie(0);
    freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    while(cin >> s){
        if(s[0] == '+' && (int)res.size() < 15000) res.insert(stoll(s.substr(1)));
        else if(!res.empty()) res.erase(*res.begin());
    }
    set<int, greater<int>> ans;
    for(int x : res) ans.insert(x);
    cout << (int)ans.size() << '\n';
    for(int x : ans) cout << x << '\n';
}
