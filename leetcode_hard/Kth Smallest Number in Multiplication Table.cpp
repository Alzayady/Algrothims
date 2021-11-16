class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int l = 1 ;
        int r = n * m ;
        int ans = 0 ;
        while(l<=r){
            int mid = (l+r) / 2 ;
            int pre = 0 ;
            for(int i = 1 ; i <= m ; i ++){
                pre += min(n , mid / i );
            }
            if(pre >=k){
                ans = mid ;
                r = mid - 1;
            }else{
                l = mid + 1 ;
            }
        }
        return ans;
    }
};
