#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define endll "\n"
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll INF = 1e15;
const int N = 3e3 + 2;
int n;
vector<int> vec;
ll dp[N][N][2];
bool vis[N][N][2];

ll solve(int l, int r, bool f) {
    if (l > r) {
        return 0;
    }
    if (vis[l][r][f]) {
        return dp[l][r][f];
    }
    vis[l][r][f]=true;
    if (f == 0) { // player 1
        return dp[l][r][f] = max(vec[l] + solve(l + 1, r, true), vec[r] + solve(l, r - 1, true));
    } else {
        return dp[l][r][f] = min(-1 * vec[l] + solve(l + 1, r, false), -1 * vec[r] + solve(l, r - 1, false));
    }

}

int main() {
    IO;
    cin >> n;
    vec.resize(n);
    for (int i = 0; i < n; i++)cin >> vec[i];
    cout<<solve(0,n-1,false);

}
