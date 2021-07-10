class Solution {
public:
    const static int N = 1e5+10;
    const int MOD = 1e9+7;
    int dp[N];
    string s ;
    int n ;
    long long  solve(int index){
        if(index == n)return 1;
        if(index > n)return 0 ;
        if(dp[index]!=-1){
            return dp[index];
        }
        long long  ans = 0;
        if(s[index]=='0'){
            return 0 ;
        }else if(s[index]=='1'){
            ans = solve(index+1) + (s[index+1] =='*' ? 9 : 1 ) * solve(index+2);
            ans%=MOD;
        }else if(s[index] == '2' ){
             ans = solve(index+1);
             if(s[index+1] == '*'){
                 ans += 6 * solve(index+2);
             }else if(s[index+1] <='6'){
                 ans += solve(index+2);
             }
            ans%=MOD;
        }else if(s[index]=='*'){
            ans =  (s[index+1] =='*' ? 9 : 1 ) * solve(index+2);
            ans%=MOD;
             if(s[index+1] == '*'){
                 ans += 6 * solve(index+2);
             }else if(s[index+1] <='6'){
                 ans += solve(index+2);
             }
            ans%=MOD;
            ans+= 9 * solve(index + 1 );
            ans%=MOD;
        }else{
            ans = solve(index+1);
        }
        return dp[index] = ans;
    }
    int numDecodings(string s) {
        this->s = s;
        this->n = s.size();
        memset(dp,-1,sizeof dp);
        return solve(0);
    }
};
