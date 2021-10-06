class Solution {
public:
    int  dp[1002][1002];
    int n , m ;
   
    int calculateMinimumHP(vector<vector<int>>& mat) {
        n =mat.size();
        m=mat[0].size();
        dp[n-1][m-1]=1;
        if(mat[n-1][m-1]<=0){
            dp[n-1][m-1]-=mat[n-1][m-1];
        }
        for(int i = n-2 ; i>=0 ; i--){
                dp[i][m-1]=max(dp[i+1][m-1]-mat[i][m-1],1);
        }
        for(int i = m-2 ; i>=0 ; i--){
             dp[n-1][i]=max(dp[n-1][i+1]-mat[n-1][i],1);
        }
        for(int i= n-2 ; i>= 0 ; i--){
            for(int j = m-2 ; j>=0 ; j--){
                dp[i][j]=max(min(dp[i+1][j],dp[i][j+1])-mat[i][j],1);
            }
        }
        return dp[0][0];
    }
};
