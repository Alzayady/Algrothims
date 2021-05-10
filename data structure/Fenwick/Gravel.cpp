#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

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
// line : https://www.codechef.com/problems/SPREAD
struct fenwick {
    vector<ll> vec;
    int n;


    fenwick(int s ){
        n = s+1;
        vec.resize(n);
    }
    void add(int ind, int val) {
        for (++ind; ind < n; ind += ind & -ind) {
            vec[ind] += val;
        }
    }

    void add_range(int l, int r, int k) {
        add(l, k);
        add(r + 1, -k);
    }

    ll get_point(int ind) {
        ll ans = 0;
        for (++ind; ind > 0; ind -= (ind & -ind)) {
            ans += vec[ind];
        }
        return ans;
    }
};

int main() {
    IO;

    int n, q, c;
    cin >> n >> q >> c;
    fenwick *f = new fenwick(n);
    f->add(0, c);
    while (q--) {
        char c;
        cin >> c;
        if (c == 'S') {
            int a, b, k;
            cin >> a >> b >> k;
            a--;
            b--;

            f->add_range(a, b, k);
        } else if (c == 'Q') {
            int p;
            cin >> p;
            p--;
            cout << f->get_point(p) << '\n';
        }
    }

}
