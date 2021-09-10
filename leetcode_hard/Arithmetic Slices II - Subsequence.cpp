class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        vector<unordered_map<long long ,int >>vec(n);
        int ans = 0;
        for(int i = n-1 ; i>=0 ; i --){
            for(int j = i +1 ; j < n ; j ++){
                long long  dif = (long long )nums[j] - (long long ) nums[i];
                ans+=vec[j][dif];
                vec[i][dif]+=vec[j][dif]+1;
            }
        }
        return ans;
    }
};
