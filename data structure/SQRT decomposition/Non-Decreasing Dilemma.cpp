#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
 #define int long long

typedef long long ll;
typedef long double ld;
using namespace std;
using namespace __gnu_pbds;

mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;
const int N = 71;
const int BLOCK = 450;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

int getBeginOfBlock(int index) {
    int b = index / BLOCK;
    return b * BLOCK;
}

int getENdOfBlock(int index) {
    int b = index / BLOCK;
    b++;
    return b * (BLOCK) - 1;
}

int n, t;
vector<int> vec;
vector<ll> ansPerBlock;
vector<int> firstAnsInBlock;
vector<int> lastAnsInBlock;

void updateBlock(int b, int i) {
    int s = i;
    int e = min(n - 1, getENdOfBlock(i));
    int last = -1;
    int pre = 0;
    int ansHere = 0;
    firstAnsInBlock[b] = -1;
    for (int j = s; j <= e; j++) {
        if (vec[j] >= last) {
            pre++;
            ansHere += pre;
            last = vec[j];
        } else {
            if (firstAnsInBlock[b] == -1) {
                firstAnsInBlock[b] = pre;
            }
            pre = 1;
            last = vec[j];
            ansHere++;
        }
    }
    if (firstAnsInBlock[b] == -1) {
        firstAnsInBlock[b] = pre;
    }
    lastAnsInBlock[b] = pre;
    ansPerBlock[b] = ansHere;
}

int32_t main() {
    IO;
    cin >> n >> t;
    vec.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    ansPerBlock.resize(BLOCK + 5, -1);
    firstAnsInBlock.resize(BLOCK + 4, -1);
    lastAnsInBlock.resize(BLOCK + 4, -1);
    for (int i = 0; i < n;) {
        int b = i / BLOCK;
        updateBlock(b, i);
        i += BLOCK;
    }
    while (t--) {
        int ty, l, r;
        cin >> ty >> l >> r;
        if (ty == 1) {
            l--;
            vec[l] = r;
            updateBlock(l / BLOCK, getBeginOfBlock(l));
        } else {
            l--;
            r--;
            ll ans = 0;
            int pre = 0; // increasing elements of all last indexes not only the last block
            int last = -1;
            for (int i = l; i <= r;) {
                int s = getBeginOfBlock(i);
                int e = getENdOfBlock(i);
                int b = i / BLOCK;
                if (s >= l and e <= r) {
                    // put entire block
                    if (vec[s] >= last) {
                        ans += firstAnsInBlock[b] * pre;
                        if (firstAnsInBlock[b] == BLOCK) {
                            pre += firstAnsInBlock[b];
                        } else {
                            pre = lastAnsInBlock[b];
                        }
                    } else {
                        pre = lastAnsInBlock[b];
                    }
                    ans += ansPerBlock[b];
                    i += BLOCK;
                    last = vec[e];
                } else {
                    if (vec[i] >= last) {
                        pre++;
                    } else {
                        pre = 1;
                    }
                    ans += pre;
                    last = vec[i];
                    i++;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
