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
    reverse(str.begin(), str.end());
    int n = str.size();
    vector<int> z(n);
    z[0] = 0;
    int left = 0;
    int right = 0;
    int m = 0;
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
        m = max(m, z[i]);
    }
    return n - m;
}

int main() {
    IO;
    int t;
    cin >> t;
    while (t--) {
        string str;
        cin >> str;
        int n = str.size();
        string cur = "";
        int ans = 0;
        for (int i = 0; i < n; i++) {
            cur += str[i];
            ans += get_(cur);
        }
        cout << ans << endl;
    }
    return 0;
}

