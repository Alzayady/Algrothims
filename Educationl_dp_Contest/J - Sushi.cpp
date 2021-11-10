#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
#define endll "\n"
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll INF = 301;
const int N = 302;
const int MOD = 1e9 + 7;

int n;
vector<int> vec;
ld dp[N][N][N];

ld solve(int a, int b, int c) {
    if (dp[a][b][c] >= 0) {
        return dp[a][b][c];
    }
    if (a == 0 && b == 0 & c == 0) {
        return 0;
    }
    ld &ans = dp[a][b][c];
    ans = 0;
    int s = a + b + c;
    ans = 1.0 * n / s;
    if (a) {
        ans += 1.0 * a / s * solve(a - 1, b, c);
    }
    if (b) {
        ans += 1.0 * b / s * solve(a + 1, b - 1, c);
    }
    if (c) {
        ans += 1.0 * c / s * solve(a, b + 1, c - 1);
    }
    return ans;
}

int main() {
    IO;
    cin >> n;
    vec.resize(n);
    int a = 0, b = 0, c = 0;
    int num;
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num == 1) {
            a++;
        } else if (num == 2) {
            b++;
        } else if (num == 3) {
            c++;
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << setprecision(20)<<solve(a, b, c) << endl;
    return 0;
}
