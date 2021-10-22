class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        int g = nums[0];
        for(int i: nums){
            g = __gcd(g,i);
        }
        return g==1;
    }
};
