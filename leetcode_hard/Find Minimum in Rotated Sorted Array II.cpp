class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int l = 1, r = n-1;
        while(l<n&&nums[l]==nums[0])l++;
        int ans=0;
        while(l<=r){
            int mid=(l+r)/2;
            if(nums[mid]<=nums[0]){
                ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        return min(nums[ans],nums[0]);
    }
};
