class Solution {
public:
    const static int N = 2*1e4+2;
    int dp[N][5];
    int n ;
    vector<vector<int>> next ;
    const int MOD = 1e9+7;
    int solve(int cur , int c){
         if(cur==n-1){
            return 1;
        }
        if(~dp[cur][c]){
            return dp[cur][c];
        }
        dp[cur][c] =0;
        for(int next_state : next[c]){
            dp[cur][c]+=solve(cur+1,next_state);
            dp[cur][c]%=MOD;
        }
        return dp[cur][c];
        
    }
    void init(int n ){
        map<char , int> char_to_state ;
        char_to_state['a'] = 0 ;
        char_to_state['e'] = 1 ;
        char_to_state['o'] = 2 ;
        char_to_state['i'] = 3 ;
        char_to_state['u'] = 4 ;
        
        next.resize(5);
        
        next[char_to_state['a']].push_back( char_to_state['e']);
        
        next[char_to_state['e']].push_back( char_to_state['a']);
        next[char_to_state['e']].push_back( char_to_state['i']);
        
        next[char_to_state['i']].push_back( char_to_state['a']);
        next[char_to_state['i']].push_back( char_to_state['e']);
        next[char_to_state['i']].push_back( char_to_state['u']);
        next[char_to_state['i']].push_back( char_to_state['o']);
        
        next[char_to_state['o']].push_back( char_to_state['i']);
        next[char_to_state['o']].push_back( char_to_state['u']);
        
        next[char_to_state['u']].push_back( char_to_state['a']);
        
        
        
        memset(dp,-1, sizeof dp[0] * n);
        this->n = n ;
    }
    int countVowelPermutation(int n) {
        init(n);
        int ans = 0 ;
        for(int i = 0 ;i < 5 ; i ++){
            ans+= solve(0,i);
            ans%=MOD;
        }
        return ans;
    }
};
