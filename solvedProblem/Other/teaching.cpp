/* Author : Triet Do Thanh - FPT University */

#include <bits/stdc++.h>

#define endl '\n'
#define int long long // Sử dụng long long cho các phép tính liên quan đến thời gian và giá trị cao

using namespace std;

typedef pair<int, int> ii; // Dùng để lưu trữ cặp số nguyên

// Kích thước tối đa của lưới N x N. N_MAX_GRID là 1000, vậy N_MAX_NODES là 1000*1000 = 1 triệu
const int N_MAX_GRID = 1002;
const int N_MAX_NODES = N_MAX_GRID * N_MAX_GRID + 7; // Kích thước mảng DSU (lớn hơn n*n một chút)

int n;
int a[N_MAX_GRID][N_MAX_GRID], t[N_MAX_GRID][N_MAX_GRID];

// Hướng di chuyển để kiểm tra các ô kề cạnh (phải và xuống)
int mx[] = {0, 1};
int my[] = {1, 0};

// Vector lưu trữ các cạnh: {{{node1, node2}, {tử số, mẫu số}}}. Tử/mẫu biểu thị giá trị 'x'.
vector<pair<ii, ii>> edges;
// Vector lưu trữ các cạnh "quan trọng": những cặp cây luôn có cùng chiều cao (giải pháp vô hạn x)
vector<ii> importantEdges;

// Kiểm tra xem tọa độ (i, j) có hợp lệ trong lưới không
bool valid(int i, int j)
{
    return (i > 0 && j > 0 && i <= n && j <= n);
}

// Xây dựng đồ thị bằng cách xác định các cạnh giữa các cây kề cạnh
void buildGraph()
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int _ = 0; _ < 2; ++_) // Kiểm tra 2 hướng: phải và xuống
            {
                int nx = i + mx[_];
                int ny = j + my[_];
                if (valid(nx, ny)) // Nếu ô kề cạnh hợp lệ
                {
                    int idNode1 = (i - 1) * n + j; // Chuyển đổi tọa độ (i,j) thành ID node duy nhất
                    int idNode2 = (nx - 1) * n + ny; // Chuyển đổi tọa độ (nx,ny) thành ID node duy nhất

                    // Tính tử số và mẫu số cho phương trình x * num2 = num1
                    // num1 = a[nx][ny] - a[i][j]
                    // num2 = t[i][j] - t[nx][ny]
                    int num1 = a[nx][ny] - a[i][j];
                    int num2 = t[i][j] - t[nx][ny];

                    if (num2 == 0) // Trường hợp mẫu số bằng 0
                    {
                        if (num1 == 0) // Tử số cũng bằng 0: 0 * x = 0. Luôn đúng với mọi x.
                        {
                            importantEdges.push_back({idNode1, idNode2}); // Cặp này luôn liên thông
                        }
                        // Nếu num1 != 0 và num2 == 0: 0 * x = num1. Vô nghiệm. Không có kết nối.
                    }
                    else // num2 != 0, có một giá trị x duy nhất
                    {
                        // Rút gọn phân số bằng cách chia cho ước chung lớn nhất (GCD)
                        int common_divisor = std::gcd(num1, num2);
                        num1 /= common_divisor;
                        num2 /= common_divisor;

                        // Đảm bảo mẫu số luôn dương để chuẩn hóa phân số.
                        // Ví dụ: 1/-2 = -1/2. Điều này quan trọng khi so sánh phân số.
                        if (num2 < 0) {
                            num1 = -num1;
                            num2 = -num2;
                        }
                        edges.push_back({{idNode1, idNode2}, {num1, num2}});
                    }
                }
            }
        }
    }
}

// Hàm so sánh các cạnh dựa trên giá trị x (phân số num1/num2)
// So sánh A.first / A.second < B.first / B.second tương đương với A.first * B.second < B.first * A.second
// (Với giả định các mẫu số đều dương, đã được chuẩn hóa trong buildGraph)
bool cmp(pair<ii, ii> A, pair<ii, ii> B)
{
    return A.second.first * B.second.second < B.second.first * A.second.second;
}

int overall_max_ans = 1; // Biến toàn cục lưu trữ kích thước thành phần liên thông lớn nhất tìm được

// Cấu trúc DSU có khả năng hoàn tác (rollback)
struct DSU_Rollback {
    int parent[N_MAX_NODES]; // Mảng cha của mỗi node
    int sz[N_MAX_NODES];     // Kích thước của tập hợp mà node đó là gốc

    // Lịch sử thay đổi cho mảng parent và sz. Lưu con trỏ và giá trị cũ để hoàn tác.
    vector<pair<int*, int>> history_parent_changes;
    vector<pair<int*, int>> history_sz_changes;

    // Khởi tạo DSU: mỗi node là một tập hợp riêng biệt, kích thước 1
    void init(int total_nodes) {
        for (int i = 1; i <= total_nodes; ++i) {
            parent[i] = i;
            sz[i] = 1;
        }
        // overall_max_ans được khởi tạo là 1 (một cây đơn lẻ)
    }

    // Tìm node gốc của một tập hợp. Không dùng path compression để dễ hoàn tác.
    int find_set(int v) {
        while (v != parent[v])
            v = parent[v];
        return v;
    }

    // Gộp hai tập hợp chứa node a và node b
    void unite_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) { // Nếu chúng thuộc hai tập hợp khác nhau
            if (sz[a] < sz[b]) // Gộp tập nhỏ hơn vào tập lớn hơn (union by size)
                swap(a, b);

            // Lưu lại thay đổi trước khi thực hiện để có thể hoàn tác
            history_parent_changes.push_back({&parent[b], parent[b]});
            parent[b] = a; // Gộp b vào a

            history_sz_changes.push_back({&sz[a], sz[a]});
            sz[a] += sz[b]; // Cập nhật kích thước tập hợp của a

            overall_max_ans = max(overall_max_ans, sz[a]); // Cập nhật kích thước thành phần lớn nhất toàn cục
        }
    }

    // Đánh dấu một "checkpoint" trong lịch sử. Các thay đổi sau checkpoint này sẽ được hoàn tác.
    void checkpoint_history() {
        history_parent_changes.push_back({nullptr, -1}); // Sentinel để đánh dấu
        history_sz_changes.push_back({nullptr, -1});     // Sentinel để đánh dấu
    }

    // Hoàn tác các thao tác DSU cho đến checkpoint gần nhất
    void rollback_history() {
        // Hoàn tác các thay đổi của parent
        while (!history_parent_changes.empty() && history_parent_changes.back().first != nullptr) {
            *(history_parent_changes.back().first) = history_parent_changes.back().second; // Khôi phục giá trị cũ
            history_parent_changes.pop_back(); // Xóa khỏi lịch sử
        }
        if (!history_parent_changes.empty()) history_parent_changes.pop_back(); // Xóa sentinel

        // Hoàn tác các thay đổi của sz
        while (!history_sz_changes.empty() && history_sz_changes.back().first != nullptr) {
            *(history_sz_changes.back().first) = history_sz_changes.back().second; // Khôi phục giá trị cũ
            history_sz_changes.pop_back(); // Xóa khỏi lịch sử
        }
        if (!history_sz_changes.empty()) history_sz_changes.pop_back(); // Xóa sentinel
    }

} dsu_manager; // Khai báo một đối tượng DSU toàn cục

// Hàm xử lý một khối các cạnh có cùng giá trị x
void process_time_block(int l, int r)
{
    // Đánh dấu checkpoint trước khi áp dụng các cạnh của block hiện tại
    dsu_manager.checkpoint_history();

    // Áp dụng các cạnh từ chỉ số 'l' đến 'r' (tất cả có cùng giá trị x)
    for (int i = l; i <= r; ++i)
    {
        auto [fi, se] = edges[i]; // fi là {node1, node2}, se là {num1, num2}
        auto [u, v] = fi;
        dsu_manager.unite_sets(u, v); // Gộp các tập hợp, tự động cập nhật overall_max_ans
    }

    // Sau khi xử lý xong block này, hoàn tác các thay đổi để DSU trở về trạng thái trước đó
    // (chỉ bao gồm các importantEdges và các kết nối cơ bản)
    dsu_manager.rollback_history();
}

void solve()
{
    cin >> n;
    // Đọc dữ liệu mảng a và t
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> t[i][j];
        }
    }

    int total_nodes = n * n;
    dsu_manager.init(total_nodes); // Khởi tạo DSU

    buildGraph(); // Xây dựng danh sách edges và importantEdges

    // Áp dụng các importantEdges vào DSU. Đây là các kết nối vĩnh viễn, không được hoàn tác.
    for (auto [u, v] : importantEdges) {
        dsu_manager.unite_sets(u, v);
    }

    // Sắp xếp các cạnh (edges) theo giá trị x (phân số num1/num2)
    sort(edges.begin(), edges.end(), cmp);

    // Duyệt qua các khối cạnh có cùng giá trị x
    int r;
    for (int l = 0; l < (int)edges.size(); l = r + 1)
    {
        r = l;
        // Tìm cuối của block có cùng giá trị x
        while (r + 1 < (int)edges.size() && edges[r + 1].second == edges[l].second)
        {
                ++r;
        }
        // Xử lý block hiện tại (từ l đến r)
        process_time_block(l, r);
    }

    cout << overall_max_ans << endl; // In ra kết quả cuối cùng
}

// Macro cho việc quản lý file (nếu cần)
#define TASK "test"

signed main()
{
    // Tối ưu tốc độ nhập xuất
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    // Phần đọc/ghi file (bỏ comment nếu cần thiết cho môi trường test)
    // if (fopen("input.txt", "r"))
    // {
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // }

    solve(); // Gọi hàm giải quyết bài toán
    return 0;
}