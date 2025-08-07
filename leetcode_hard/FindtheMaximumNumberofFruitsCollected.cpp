class Solution {
public:
    int n ;
    bool valid(int i , int j ){
        if(i == n || j == n || i == -1 || j == -1) return false;
        return true;
    }
    int solveTop(int i , int j ,vector<vector<int>>& fruits , vector<vector<int>>& dp){
        if(!valid(i,j)) return -10000000;
        int cur = n - 1 - i ;
        if(cur == 0){
            if(i != n - 1  || j != n-1)  return -10000000;
            return 0;
        }
        if(j <= (n-1) / 2 ) return -10000000;
        if(dp[i][j] != -1 ) return dp[i][j];
        int op1 = solveTop( i + 1 , j , fruits, dp);
        int op2 = solveTop( i + 1 , j -1   , fruits, dp);
        int op3 = solveTop( i + 1 , j + 1 , fruits, dp);
         dp[i][j] = fruits[i][j] + max({op1, op2, op3});
        return dp[i][j];
    }

    int solveRight(int i , int j ,vector<vector<int>>& fruits , vector<vector<int>>& dp){
        if(!valid(i,j)) return -10000000;
        int cur = n - 1 - j ;
        if(cur == 0){
            if(i != n - 1  || j != n-1)  return -10000000;
            return 0;
        }
        if(i <= (n-1) / 2 ) return -10000000;
        if(dp[i][j] != -1 ) return dp[i][j];
        int op1 = solveRight( i - 1 , j + 1, fruits, dp);
        int op2 = solveRight( i  + 1 , j + 1 , fruits, dp);
        int op3 = solveRight( i  ,    j + 1 , fruits, dp);
        return dp[i][j] = fruits[i][j] + max({op1, op2, op3});
    }


    int maxCollectedFruits(vector<vector<int>>& fruits) {
        n = fruits.size();
        vector<vector<int>> dp(n , vector<int>(n,-1));
        int ans = 0 ;
        for(int i = 0 ; i < n ; i++){
            ans += fruits[i][i];
            fruits[i][i] = 0;
        }
        ans += solveTop(0 , n - 1, fruits, dp);
        vector<vector<int>> dp2(n , vector<int>(n,-1));
        ans += solveRight(n - 1 , 0 , fruits, dp2);
        return ans;
    }
};
