class Solution {
public:
    int dp[10001][101];
    
    int solve(int k, int n) {
        if(n==0){
            return 0;
        }
        if(k<=0){
            return 100000;
        }
        if(dp[n][k]!=-1){
            return dp[n][k];
        }
        int l = 1 ;
        int r = n ;
        while(l + 1 < r){
            int mid = (l + r )/ 2;
            int t1 = solve(k-1, mid-1); 
            int t2 = solve(k,n-mid) ;
            if(t1 < t2 ){
                l = mid ; 
            }else  {
                r = mid ;
            }
        }
        return dp[n][k] = 1 + min(max(solve(k-1, l-1),solve(k , n - l )),
                      max(solve(k-1, r-1),solve(k , n - r )));
        
        
    }
        int superEggDrop(int k, int n) {
            memset(dp,-1,sizeof dp);
            return solve(k,n);
        }
};
