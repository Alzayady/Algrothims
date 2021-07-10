class Solution {
public:
    vector<int> dp;
    const int MOD = 1e9 + 7;
    string s;
    int n;

    long long solve_one(int index) {
        return solve(index + 1) + (s[index + 1] == '*' ? 9 : 1) * solve(index + 2);
    }

    long long solve_two(int index) {
        long long ans = solve(index + 1);
        if (s[index + 1] == '*') {
            ans += 6 * solve(index + 2);
        } else if (s[index + 1] <= '6') {
            ans += solve(index + 2);
        }
        return ans;
    }

    long long solve(int index) {
        if (index == n)return 1;
        if (index > n)return 0;
        if (dp[index] != -1) {
            return dp[index];
        }
        long long ans = 0;
        if (s[index] == '0') {
            ans = 0 ;
        } else if (s[index] == '1') {
            ans = solve_one(index);
        } else if (s[index] == '2') {
            ans = solve_two(index);
        } else if (s[index] == '*') {
            ans = solve_one(index) + solve_two(index) + 7 * solve(index + 1);
        } else {
            ans = solve(index + 1);
        }

        return dp[index] = ans % MOD;
    }

    int numDecodings(string s) {
        this->s = s;
        this->n = s.size();
        dp.resize(n, -1);
        return solve(0);
    }
};
