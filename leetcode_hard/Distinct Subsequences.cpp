class Solution {
public:
    const static int N = 1001;
    int dp[N][N];
    string a ;
    string b ;
    int n , m ;
    int solve(int   l , int r ){
        if(dp[l][r]!=-1){
            return dp[l][r];
        }
        if(r == m){
            return 1;
        }
        if(l==n){
            return 0 ;
        }
        int ans = solve(l+1,r);
        if(a[l]==b[r]){
            ans += solve(l+1,r+1);
        }
        return dp[l][r] = ans;
    }
    int numDistinct(string s, string t) {
         n = s.size();
         m = t.size();
         a =s ;
         b =t;
         memset(dp,-1,sizeof dp);
        return solve(0,0);
    }
};
