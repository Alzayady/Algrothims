class Solution {
public:
    string a ;
    string b ;
    const static int N = 31;
    int dp[N][N][N][N];
    int solve(int l1 , int r1 , int l2 , int r2){
        if(dp[l1][r1][l2][r2]!=-1){
            return dp[l1][r1][l2][r2];
        }
        if(l1==r1){
            assert(l2 == r2);
            return a[l1] == b[l2];
        }
        int ans = 0 ;
        for(int i = l1 ; i< r1 ; i++){
            bool can = solve(l1,i,l2,l2+(i-l1)) and solve(i+1,r1,l2+i-l1+1,r2);
            bool can2 = solve(l1,i,r2-(i-l1),r2) and solve(i+1,r1,l2,l2+(r1-i-1));
            if(can || can2){
                ans = 1;
                break;
            }
        }
        return dp[l1][r1][l2][r2] = ans;
    }
    bool isScramble(string s1, string s2) {
        a = s1;
        b = s2;
        memset(dp,-1,sizeof dp);
        int n = a.size();
        return solve(0,n-1,0,n-1);
    }
};
