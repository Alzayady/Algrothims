#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;
#define int long long

// link :: https://vjudge.net/problem/LightOJ-1205
vector<int> nums;
int dp[20][20][2][2];

int solveDp(int index, bool smaller, bool greaterOnOtherSide, int preNums) {
    if (dp[index][preNums][smaller][greaterOnOtherSide] != -1) {
        return dp[index][preNums][smaller][greaterOnOtherSide];
    }
    int zeros = index - preNums;
    int n = nums.size() - zeros;
    int curIndex = index - zeros;
    int middle = (n - 1) / 2;
    if (curIndex > middle) {
        if (greaterOnOtherSide) {
            return smaller;
        } else {
            return 1;
        }
    }
    if (index == nums.size())return 1;
    int &ans = dp[index][preNums][smaller][greaterOnOtherSide];
    ans = 0;
    int limit;
    if (smaller) {
        limit = 9;
    } else {
        limit = nums[index];
    }

    for (int i = 0; i <= limit; i++) {
        if (i == 0 and preNums == 0) {
            ans += solveDp(index + 1, 1, 0, 0);
            continue;
        }
        int nextS = smaller;
        if (nextS == 0 and i < limit) nextS = 1;
        int slide = n - curIndex - 1;
        bool nextGreater = greaterOnOtherSide;
        if (nums[slide] == i);
        else if (nums[slide] < i) nextGreater = 1;
        else nextGreater = 0;
        int nx = solveDp(index + 1, nextS, nextGreater, preNums + 1);
        ans += nx;
    }
    return ans;
}

int solve(int num) {
    if (num < 0)return 0;
    if (num == 0)return 1;
    nums.clear();
    while (num) {
        nums.push_back(num % 10);
        num /= 10;
    }
    memset(dp, -1, sizeof dp);
    reverse(nums.begin(), nums.end());
    return solveDp(0, 0, 0, 0);
}

int solveTest(int a, int b) {
    if (b < a)swap(a, b);
    a = solve(a - 1);
    b = solve(b);
    return b - a;
}

bool p(int num) {
    vector<int> vec;
    while (num) {
        vec.push_back(num % 10);
        num /= 10;
    }
    int p1 = 0;
    int p2 = vec.size() - 1;
    while (p1 < p2) {
        if (vec[p1] != vec[p2])return 0;
        p1++;
        p2--;
    }
    return 1;
}

int solveBrute(int a, int b) {
    if (b < a)swap(a, b);
    int ans = 0;
    for (int i = a; i <= b; i++) {
        if (p(i)) {
            ans++;
        }
    }
    return ans;
}

void compare() {
    while (true) {
        int a = rng() % 100000;
        int b = rng() % 100000;
        int ans1 = solveTest(a, b);
        int ans2 = solveBrute(a, b);
        if (ans2 != ans1) {
            cout << ans1 << ' ' << ans2 << endl;
            cout << a << " " << b << endl;
            assert(false);
        } else {
            cout << "Accepted ok both are  ::" << ans1 << endl;
        }
    }
}

int32_t main() {
//    compare();
    IO;
    int t;
    cin >> t;
    int tt = 1;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << "Case " << tt++ << ": " << solveTest(a, b) << endl;
    }
    return 0;
}
