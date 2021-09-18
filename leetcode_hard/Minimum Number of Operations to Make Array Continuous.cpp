class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;
        sort(nums.begin(),nums.end());
        map<int , int >all;
        for(auto it: nums){
            all[it]++;
        }
        vector<int>dub(n,0);
        for(int i = 1 ;i < n ; i ++){
            dub[i] = dub[i-1];
            if(nums[i]==nums[i-1])dub[i]++;
        }
        auto range =[&](int l , int r){
            int ans = dub[r];
            if(l){
                ans -= dub[l-1];
            }
            return ans;
        };
        for(int i = 0; i < n ; i++){
            int limit = nums[i] + n ;
            auto lo = lower_bound(nums.begin(),nums.end(),limit) - nums.begin();
            int ans_here = i + n - lo + range(i,lo-1);
            if(all[limit-1]==0 and ans_here ==0)ans_here++;
            ans = min(ans,ans_here);
        }
        return ans;
    }
};
