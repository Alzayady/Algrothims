#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
typedef unsigned long long uld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;

uld seed = 12221;
const int N = 1e5;

int main() {
    IO;
    vector<uld> pows(N);
    pows[0] = 1;
    for (int i = 1; i < N; i++) {
        pows[i] = pows[i - 1] * seed;
    }

    int n;
    while (cin >> n) {
        string str;
        string all;
        cin >> str >> all;
        if (str.size() > all.size()) {
            cout << endl;
            continue;
        }
        uld hastW = 0;
        for (int i = 0; i < (int) str.size(); i++) {
            hastW *= seed;
            hastW += str[i] - 'a' + 1;
        }
        uld curHash = 0;
        for (int i = 0; i < (int) str.size(); i++) {
            curHash *= seed;
            curHash += all[i] - 'a' + 1;
        }
        int e = (int) all.size() - (int) str.size();
        vector<int> ans;
        if (curHash == hastW)ans.push_back(0);
        for (int i = 0; i <= e; i++) {
            curHash -= pows[(int) str.size() - 1] * (all[i] - 'a' + 1);
            curHash *= seed;
            curHash += all[i + str.size()] - 'a' + 1;
            if (curHash == hastW) {
                ans.push_back(i + 1);
            }
        }
        for (auto it: ans) {
            cout << it << endl;
        }
        cout << endl;
    }
  return 0;
}
