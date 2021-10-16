#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 1e9 + 7;
const float EBS = 1e-9;
const int INF = 1e8;
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
const static int N = 1e5 + 10;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

#define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>
// Finding the number of element  strictly less than k=4 o_set.order_of_key(4)
ll BLOCK_SIZE;

struct query {
    ll index;
    ll l;
    ll r;
    ll block;

    query() {

    }

    query(int l, int r, int index) {
        this->l = l;
        this->r = r;
        this->index = index;
        block = l / BLOCK_SIZE;
    }

    bool operator<(const query &y) const {
        if (block != y.block) {
            return block < y.block;
        }
        return r < y.r;
    }
};

int main() {
    IO;
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    vector<ll> pre(n + 1);
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] ^ vec[i - 1];
    }
    vector<query> q;
    BLOCK_SIZE = sqrt(m);
    for (int i = 0; i < m; i++) {
        ll l, r;
        cin >> l >> r;
        q.push_back(query(l, r, i));
    }
    sort(q.begin(), q.end());
    ll l = 0, r = -1;
    vector<ll> cur(1e7 + 100);
    vector<ll> ret(m);
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        pair<ll, ll> p = {q[i].l, q[i].r};
        while (r < p.second) {
            ll v = pre[++r];
            ans += cur[v ^ k];
            cur[v]++;
        }
        while (r > p.second) {
            ll v = pre[r--];
            cur[v]--;
            ans -= cur[v ^ k];
        }

        while (l >= p.first) {
            ll v = pre[--l];
            ans += cur[v ^ k];
            cur[v]++;
        }
        while (l + 1  < p.first) {
            ll v = pre[l++];
            cur[v]--;
            ans -= cur[v ^ k];
        }
        ret[q[i].index] = ans;
    }
    for (int i = 0; i < m; i++) {
        cout << ret[i] << " ";
    }
    cout << endl;
    return 0;
}
