#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
#define endll "\n"
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll INF = 301;
const int N = 40 + 2;
const int MOD = 1e9 + 7;
vector<int> vec;
int n;

struct sparse_table {
    vector<vector<int>> arr;

    sparse_table() {
        arr.resize(n + 1, vector<int>(22));
        for (int i = 0; i < n; i++) {
            arr[i][0] = vec[i];
        }
        for (int i = 1; i < 20; i++) {
            for (int j = 0; (j + (1ll << i)) <= n; j++) {
                arr[j][i] = __gcd(arr[j][i - 1], arr[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    int query(int l, int r) {
        int s = log2(r - l + 1);
        return __gcd(arr[l][s], arr[r - (1 << s ) +1 ][s]);
    }

    int bs(int f ,int gcd, int l) {
        int r = n-1;
        int ans = l ;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (query(f, mid) == gcd) {
                l = mid + 1;
                ans = mid;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }

};

int main() {
    IO;
    cin >> n;
    vec.resize(n);
    for (int i = 0; i < n; i++)cin >> vec[i];
    map<int, ll> m;
    sparse_table table;
    for (int i = 0; i < n; i++) {
        int index = i;
        int cur_gcd = vec[i];
        while (index != n) {
            int next = table.bs(i,cur_gcd, index);
            m[cur_gcd] += (next - index +1 );
            index = next + 1 ;
            if (index!= n)
                cur_gcd = table.query(i, index);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int num;
        cin >> num;
        cout << m[num] << '\n';
    }
    return 0;
}
