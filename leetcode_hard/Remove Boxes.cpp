class Solution {
public:
    int dp[101][101][101];
    int n ;
    vector<int>v;
    int removeBoxes(vector<int>& vec) {
        memset(dp,-1,sizeof dp);
        n = vec.size();
        v =vec;
        return solve(0,n-1,0);
        
    }
    int solve(int l , int r , int k ) {
        if(dp[l][r][k]!=-1)return dp[l][r][k];
        if(l==r)return (k+1)*(k+1) ;
        if(l>r)return 0 ;
        int ans = (k+1)*(k+1) + solve(l+1,r,0) ;
        for(int i = l +1; i<=r ; i++){
            if(v[i] == v[l]){
                ans = max(ans,solve(i,r,k+1)+solve(l+1,i-1,0));
            }
        }
        return dp[l][r][k] = ans;
        
    }
};
