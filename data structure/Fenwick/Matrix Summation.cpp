#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;
using namespace __gnu_pbds;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
vector<int> sei;
vector<int> dx = {1, 0, 0, -1};
vector<int> dy = {0, -1, 1, 0};

// link :  https://www.spoj.com/problems/MATSUM/
struct fenwick {
    int n;
    vector <vector<ll>> mat;

    fenwick(int s) {
        n = s + 1;
        mat.resize(n, vector<ll>(n, 0));
    }

    void update(int x, int y, int val) {
        for (int cur_x = x + 1; cur_x < n; cur_x += (cur_x & -cur_x)) {
            for (int cur_y = y + 1; cur_y < n; cur_y += (cur_y & -cur_y)) {
                mat[cur_x][cur_y] += val;
            }
        }
    }

    ll sum(int x, int y) {
        ll ans = 0;
        for (int cur_x = x + 1; cur_x > 0; cur_x -= (cur_x & -cur_x)) {
            for (int cur_y = y + 1; cur_y > 0; cur_y -= (cur_y & -cur_y)) {
                ans += mat[cur_x][cur_y];
            }
        }
        return ans;
    }

    ll sum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) + sum(x1 - 1, y1 - 1) - sum(x1 - 1, y2) - sum(x2, y1 - 1);
    }
};

int main() {
    IO;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        fenwick *f = new fenwick(n);
        vector <vector<int>> vec(n, vector<int>(n, 0));
        while (true) {
            string str;
            cin >> str;
            if (str == "SET") {
                int a, b, c;
                cin >> a >> b >> c;
                f->update(a, b, -vec[a][b] + c);
                vec[a][b] = c;
            } else if (str == "SUM") {
                int a, b, c, d;
                cin >> a >> b >> c >> d;
                cout << f->sum(a, b, c, d) << "\n";
            } else {
                break;
            }
        }
    }
}
