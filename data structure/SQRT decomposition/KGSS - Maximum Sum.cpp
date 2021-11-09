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
const int N = 71;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

int main() {
    IO;
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    int b = sqrt(n);
    vector<pair<int, int >> send(b + 10, {-1, -1}); // start and end
    vector<pair<int, int >> m(b + 10);// max two
    vector<map<int, int >> blocks(b + 10);
    vector<int> start;
    for (int i = 0; i < n; i++) {
        int bb = i / b;
        if (send[bb].first == -1) {
            send[bb].first = i;
        }
        send[bb].second = i;
        vector<int> te = {m[bb].first, m[bb].second, vec[i]};
        sort(te.begin(), te.end());
        m[bb].first = te[1];
        m[bb].second = te[2];
        blocks[bb][vec[i]]++;
    }
    int t;
    cin >> t;
    while (t--) {
        char c;
        cin >> c;
        int l, r;
        cin >> l >> r;

        if (c == 'Q') {
            l--;
            r--;
            pair<int, int> ans;
            auto updateAns = [&](int v) {
                if (v >= ans.second) {
                    ans.first = ans.second;
                    ans.second = v;
                } else if (v > ans.first) {
                    ans.first = v;
                }
            };
            for (int i = l; i <= r;) {
                int bb = i / b;
                if (send[bb].first >= l and send[bb].second <= r) {
                    updateAns(m[bb].first);
                    updateAns(m[bb].second);
                    i = send[bb].second + 1;
                } else {
                    updateAns(vec[i]);
                    i++;
                }
            }
            cout << ans.first + ans.second << endl;
        } else {
            l--;
            int bb = l / b;
            blocks[bb][vec[l]]--;
            if (blocks[bb][vec[l]] == 0) {
                blocks[bb].erase(vec[l]);
            }
            blocks[bb][r]++;
            vec[l] = r;
            auto it = blocks[bb].end();
            it--;
            if (it->second >= 2) {
                m[bb].first = it->first;
                m[bb].second = it->first;
            } else {
                m[bb].second = it->first;
                if (it != blocks[bb].begin()) {
                    it--;
                    m[bb].first = it->first;
                }

            }
        }
    }
    return 0;
}/*
 1
5
3
U
1 5
Q
1 1

 */
