class Solution {
public:
    int MOD = 1e9 + 7 ;
    vector<vector<long long>> table;
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        buildPascal(n);
        return numOfWays2(nums) - 1;
    }
    int numOfWays2(vector<int>& nums, int root = 0 , int limit_small = -10000 , int limit_big = 100000 ) {
        if(root == nums.size()) return 1;
        if(root == -1) return 1;
        int left = 0 ;
        int right = 0 ;
        int root_left = -1;
        int root_right = -1;
        int big_left = -1000000;
        int small_right = 1000000;
        int n = nums.size();
        for(int i = root + 1 ; i < n; i ++) {
            if(nums[i] > limit_big)continue;
            if(nums[i] < limit_small)continue;
            if(nums[i] > nums[root]) {
                right ++ ;
                small_right = min(small_right, nums[i]);
            }
            else {
                left ++ ; 
                big_left = max(big_left, nums[i]);
            }
            if(right == 1 and root_right == -1 ) root_right = i ;
            else if (left == 1 and root_left == -1 ) root_left = i ;
        }

        long long solve_left = numOfWays2(nums,root_left, limit_small , nums[root]);
        long long solve_right = numOfWays2(nums,root_right, nums[root] , limit_big );
        
        long long solve_here = table[left + right][left];
        solve_here%=MOD;
        long long ans = (solve_left * solve_right ) %MOD * solve_here ;
        ans %= MOD;
        return ans;
    }


void buildPascal(int n) {
        table.assign(n + 1, vector<long long>(n + 1, 1));
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MOD;
            }
        }
    }
};
