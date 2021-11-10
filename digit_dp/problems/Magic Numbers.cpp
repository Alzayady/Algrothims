#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

int m , d ;
string a , b ;
int len ;
const int N = 2e3 +10;
const int MOD = 1e9 +7;
int dp[N][N][4];
int solve(int index , int mod , int type) {
    if (index == len) {
        if (mod == 0) {
            return 1;
        }
        return 0;
    }
    int &ans = dp[index][mod][type];
    if (ans != -1)return ans;
    ans = 0;
    if (index % 2 == 0) { // odd
        int s = a[index] - '0';
        int e = b[index] - '0';
        if (type == 0) { // a = 1874   cur = 18
            if (s != d)
                ans += solve(index + 1, (mod * 10 + s) % m, 0);
            for (int i = s + 1; i <= 9; i++) {
                if (i == d)continue;
                ans += solve(index + 1, (mod * 10 + i) % m, 1);
                ans %= MOD;
            }
            // a = 10000 b = 66666 cur = 10060  -> it can happen   :)

            return ans;
        }

        if (type == 1) { // a =1874 cur = 17
            e = 9;
            for (int i = 0; i <= e; i++) {
                if (i == d)continue;
                ans += solve(index + 1, (mod * 10 + i) % m, 1);
                ans %= MOD;
            }
            return ans;
        }
        if (type == 2) { // a = 1874   b = 8748
            s = 0;
            for (int i = s; i < e; i++) {
                if (i == d)continue;
                ans += solve(index + 1, (mod * 10 + i) % m, 1);
                ans %= MOD;
            }
            if (d != e) {
                ans += solve(index + 1, (mod * 10 + e) % m, 2);
                ans %= MOD;
            }
            return ans;
        }
        if (type == 3) {
            if (a[index] == b[index]) {
                if (a[index] - '0' == d)return ans = 0;
                return ans = solve(index + 1, (mod * 10 + s) % m, 3);
            } else {
                if (a[index] - '0' != d) ans += solve(index + 1, (mod * 10 + a[index] - '0') % m, 0);
                for (int i = s + 1; i < e; i++) {
                    if (i == d)continue;
                    ans += solve(index + 1, (mod * 10 + i) % m, 1);
                    ans %= MOD;
                }
                if (e != d) {
                    ans += solve(index + 1, (mod * 10 + e) % m, 2);
                    ans %= MOD;
                }
                return ans;
            }
        }
    }

    if (type == 0) {
        if (d < a[index] - '0')return ans = 0;
        if (d == a[index] - '0') {
            return ans = solve(index + 1, (mod * 10 + d) % m, 0);
        }
        return ans = solve(index + 1, (mod * 10 + d) % m, 1);
    }

    if (type == 1) {
        return ans = solve(index + 1, (mod * 10 + d) % m, 1);
    }
    if (type == 2) {
        if (b[index] - '0' < d)return ans = 0;
        if (b[index] - '0' == d)
            return ans = solve(index + 1, (mod * 10 + d) % m, 2);
        return ans = solve(index + 1, (mod * 10 + d) % m, 1);
    }
    if (type == 3) {
        if (a[index] == b[index]) {
            if (a[index] - '0' == d) {
                return ans = solve(index + 1, (mod * 10 + d) % m, 3);
            } else
                return ans = 0;
        }
        if (d < a[index] - '0' || d > b[index] - '0')return ans = 0;
        if (d == a[index] - '0') {
            return ans = solve(index + 1, (mod * 10 + d) % m, 0);
        }
        if (d == b[index] - '0') {
            return ans = solve(index + 1, (mod * 10 + d) % m, 2);
        }
        return ans = solve(index + 1, (mod * 10 + d) % m, 1);

    }
    return 0;
}

int main() {
    IO;
    cin >> m >> d;
    cin >> a >> b;
    len = a.size();
    memset(dp, -1, sizeof(dp));
    cout<<solve(0,0,3)<<endl;
}
