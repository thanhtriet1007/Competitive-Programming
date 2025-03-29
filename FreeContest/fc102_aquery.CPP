#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
struct Warrior {
    // Chỉ lưu lại đối với những chiến binh cần “cross” (với P khác Q)
    // Lưu A = min(S, T), B = max(S, T)
    ll A, B;
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int K, N;
    cin >> K >> N;
    // Tổng chi phí của những chiến binh không cần cầu (không cross)
    ll nonCrossCost = 0;
    // Danh sách các chiến binh “cross”
    vector<Warrior> cross;
    // Mỗi dòng gồm: P_i, S_i, Q_i, T_i.
    // Lưu ý: Nếu P_i và Q_i giống nhau thì chiến binh không cần vượt sông.
    for (int i=0; i<N; i++){
        char p, q;
        ll s, t;
        cin >> p >> s >> q >> t;
        if(p == q){
            nonCrossCost += ( s > t ? s - t : t - s );
        } else {
            ll A = min(s, t), B = max(s, t);
            cross.push_back({A, B});
        }
    }
 
    // Nếu không có chiến binh cross, kết quả chỉ là nonCrossCost.
    if(cross.empty()){
        cout << nonCrossCost << "\n";
        return 0;
    }
 
    // Với mỗi chiến binh cross, nếu cầu “được đặt lý tưởng” (nằm trong [A,B])
    // thì chi phí tối ưu là: (B-A+1).
    // Nếu không, chi phí sẽ tăng thêm 2*(khoảng cách từ vị trí cầu đến biên [A,B]).
    // Như vậy, tổng chi phí của các chiến binh cross nếu dùng cây cầu tại vị trí X sẽ là:
    //   sum_{i in cross} [(B_i-A_i+1) + 2*d_i(X)]
    // với d_i(X)=0 nếu X in [A_i,B_i], nếu X < A_i thì = A_i-X, nếu X > B_i thì = X-B_i.
 
    ll ans = LLONG_MAX;
 
    // Với K = 1
    if(K == 1){
        // Ta “gộp” tất cả các chiến binh cross lại.
        // Tổng chi phí cơ bản:
        ll baseCost = 0;
        ll globalA = 0, globalB = 1e18;
        for(auto &w : cross){
            baseCost += (w.B - w.A + 1);
            globalA = max(globalA, w.A);
            globalB = min(globalB, w.B);
        }
        // Nếu giao nhau của tất cả các [A_i, B_i] rỗng (globalA > globalB)
        // thì extra = 2*(globalA - globalB), ngược lại extra = 0.
        ll extra = 0;
        if(globalA > globalB) extra = 2 * (globalA - globalB);
        ll total = baseCost + extra + nonCrossCost;
        cout << total << "\n";
        return 0;
    }
    // Với K = 2
    else if(K == 2){
        // Sắp xếp theo A (min(S,T))
        sort(cross.begin(), cross.end(), [](const Warrior &w1, const Warrior &w2){
            return w1.A < w2.A;
        });
        int m = cross.size();
        // Tiền xử lý: tính prefix cho nhóm bên trái.
        vector<ll> prefBase(m), prefMaxA(m), prefMinB(m);
        {
            prefBase[0] = (cross[0].B - cross[0].A + 1);
            prefMaxA[0] = cross[0].A;
            prefMinB[0] = cross[0].B;
            for (int i = 1; i < m; i++){
                prefBase[i] = prefBase[i-1] + (cross[i].B - cross[i].A + 1);
                prefMaxA[i] = max(prefMaxA[i-1], cross[i].A);
                prefMinB[i] = min(prefMinB[i-1], cross[i].B);
            }
        }
        // Tính suffix cho nhóm bên phải.
        vector<ll> sufBase(m), sufMaxA(m), sufMinB(m);
        {
            sufBase[m-1] = (cross[m-1].B - cross[m-1].A + 1);
            sufMaxA[m-1] = cross[m-1].A;
            sufMinB[m-1] = cross[m-1].B;
            for (int i = m-2; i >= 0; i--){
                sufBase[i] = sufBase[i+1] + (cross[i].B - cross[i].A + 1);
                sufMaxA[i] = max(sufMaxA[i+1], cross[i].A);
                sufMinB[i] = min(sufMinB[i+1], cross[i].B);
            }
        }
 
        ll best = LLONG_MAX;
        // Xét trường hợp nhóm bên trái rỗng (tức toàn bộ trong bên phải)
        {
            ll costRight = sufBase[0] + 2 * max(0LL, sufMaxA[0] - sufMinB[0]);
            best = min(best, costRight);
        }
        // Nhóm bên phải rỗng (toàn bộ bên trái)
        {
            ll costLeft = prefBase[m-1] + 2 * max(0LL, prefMaxA[m-1] - prefMinB[m-1]);
            best = min(best, costLeft);
        }
        // Duyệt tất cả các vị trí phân chia: để nhóm trái gồm các chiến binh ở chỉ số [0,i] và
        // nhóm phải gồm [i+1, m-1].
        for (int i = 0; i < m-1; i++){
            ll costLeft = prefBase[i] + 2 * max(0LL, prefMaxA[i] - prefMinB[i]);
            ll costRight = sufBase[i+1] + 2 * max(0LL, sufMaxA[i+1] - sufMinB[i+1]);
            best = min(best, costLeft + costRight);
        }
 
        ll total = best + nonCrossCost;
        cout << total << "\n";
        return 0;
    }
 
    return 0;
}
