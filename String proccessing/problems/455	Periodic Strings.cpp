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

int get_(string str) {
    int n = str.size();
    vector<int> z(n);
    z[0] = 0;
    int left = 0;
    int right = 0;
    for (int i = 1; i < n; i++) {
        if (i > right) {
            left = right = i;
            while (right < n and str[right] == str[right - left]) {
                right++;
            }
            z[i] = right - left;
            right--;
        } else {
            int k = i - left;
            if (z[k] + i <= right) {
                z[i] = z[k];
            } else {
                left = i;
                while (right < n and str[right] == str[right - left]) {
                    right++;
                }
                z[i] = right - left;
                right--;
            }
        }
    }
    map<int, int> ans;
    for (int i = 1; i < n; i++) {
        ans[z[i]]++;
    }
    vector<pair<int, int >> vec;
    for (auto it : ans) {
        vec.push_back({it.first, it.second});
    }
    for (int i = vec.size() - 2; i >= 0; i--) {
        vec[i].second += vec[i + 1].second;
    }
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].first * (vec[i].second + 1) == n) {
            cout << vec[i].first << endl;
            return 0;
        }
    }
    cout << n << endl;
    return 0;
}

int main() {
    IO;
    int t;
    cin >> t;
    while (t--) {
        string str;
        cin >> str;
        get_(str);
        if (t) {
            cout << endl;
        }
    }
    return 0;
}

