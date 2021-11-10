#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
// #define int long long

typedef long long ll;
typedef long double ld;
using namespace std;
using namespace __gnu_pbds;

mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;
const int N = 1e5;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

priority_queue<int, vector<int>, greater<int> > min_pq;

struct sparseTable {
    vector<vector<int>> table;

    sparseTable();

    sparseTable(vector<int> vec) {
        int n = vec.size();
        table.resize(n, vector<int>(20));
        for (int i = 0; i < n; i++) {
            table[i][0] = vec[i];
        }
        for (int i = 1; i <= 20; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                table[j][i] = __gcd(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    int query(int a, int b) {
        int s = log2(b - a + 1);
        return __gcd(table[a][s], table[b - (1 << s) + 1][s]);
    }
};

int32_t main() {
    IO;
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    sparseTable s = sparseTable(vec);
    map<int, vector<int>> m;
    for (int i = 0; i < n; i++) {
        m[vec[i]].push_back(i);
    }
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int g = s.query(a, b);
        int h = std::upper_bound(m[g].begin(), m[g].end(), b) - m[g].begin();
        int hh = std::lower_bound(m[g].begin(), m[g].end(), a) - m[g].begin();
        int ans = b - a + 1 - h + hh;
        cout << ans << "\n";
    }
    return 0;
}
