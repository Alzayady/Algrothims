class Solution {
public:
    string a ,b ;
    int n , m ;
    vector<vector<int>>dp;
    int solve(int l , int r ){
        if(dp[l][r]!=-1){
            return dp[l][r];
        }
        if(l==n and r == m)return 1;
        if(r==m)return 0 ;
        if(l==n){
            if(b[r]=='*'){
                return dp[l][r] = solve(l,r+1);
            }else{
                return 0 ;
            }
        }
        bool ans = 0; 
      
        if(b[r]=='*'){
            ans|= (solve(l+1,r));
            ans|=(solve(l,r+1));
        }else if(b[r]=='?'){
            ans |=solve(l+1,r+1);
        }else{
            if(a[l]!=b[r]){
                ans = 0;
            }else{
                ans |= solve(l+1,r+1);
            }
        }
        return dp[l][r]= ans;
        
        
    }
    bool isMatch(string s, string p) {
        a =s;
        b = p;
        n = s.size();
        m = p.size();
        dp.resize(n+10,vector<int>(m+10,-1));
        return solve(0,0);
    }
};
