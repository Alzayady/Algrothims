#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

//#define int long long
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int BLOCK_SIZE = 350;

int main() {
    IO;
    int n, t;
    cin >> n >> t;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
//    BLOCK_SIZE = 350;
    vector<int> next(n);
    vector<int> count(n);
    vector<int> block(n);
    for (int i = 0; i < n; i++) {
        block[i] = i / BLOCK_SIZE;
    }
    auto reschudle = [&](int i) {
        int nx = vec[i] + i;
        if (nx >= n) {
            count[i] = 1;
            next[i] = nx;
        } else {
            if (block[nx] == block[i]) {
                count[i] = count[nx] + 1;
                next[i] = next[nx];
            } else {
                count[i] = 1;
                next[i] = nx;
            }
        }
    };
    for (int i = n - 1; i >= 0; i--) {
        reschudle(i);
    }
    while (t--) {
        int ty;
        cin >> ty;
        if (ty == 0) {
            int a, b;
            cin >> a >> b;
            a--;
            vec[a] = b;
            int cur = a;
            while (cur >= 0 and block[cur] == block[a]) {
                reschudle(cur);
                cur--;
            }
        } else {
            int cur;
            cin >> cur;
            cur--;
            int ans = 0;
            int nx = cur;
            int last = cur;
            while (nx < n) {
                ans += count[nx];
                last = nx;
                nx = next[nx];
            }
            while (vec[last] + last <= n - 1) {
                last += vec[last];
            }

            cout << last + 1 << " " << ans << endl;
        }
    }
    return 0;
}
