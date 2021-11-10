#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
#define endll "\n"
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll INF = 301;
const int N = 40 + 2;
const int MOD = 1e9 + 7;
int n;
vector<int> vec;

struct table {
    vector<vector<int>> table_vec;

    table() {
        table_vec.resize(n + 1, vector<int>(22));
        build();
    }

    void build() {
        for (int i = 0; i < n; i++) {
            table_vec[i][0] = vec[i];
        }
        for (int i = 1; i < 22; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                table_vec[j][i] = min(table_vec[j][i - 1], table_vec[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    int query(int l, int r) {
        int s = log2(r - l + 1);
        return min(table_vec[l][s], table_vec[r - (1 << s) + 1][s]);
    }
};

int main() {
    IO;
    cin >> n;
    vec.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    table table;
    int t;
    cin>>t;
    while (t--){
        int l , r ;
        cin>>l>>r;
        cout<<table.query(l,r)<<endll;
    }
    return 0;
}
