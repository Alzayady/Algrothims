class Solution {
public:
    vector<int> nums;
    pair<int , int > dp[10][2];
    pair<int , int > solve(int index , bool smaller = 0 ){ // return all and ans 
        if(index == nums.size())return {1,0};
        if(dp[index][smaller].first!=-1){
            return dp[index][smaller];
        }
        int limit = 0 ;
        if(smaller){
            limit = 9;
        }else{
            limit = nums[index];
        }
        pair<int, int > ans = {0,0} ;
        for(int i = 0 ; i <= limit ; i++){
            bool nextS = smaller ;
            if(nextS==0 and i < limit )nextS = 1 ;
            pair<int , int > ret= solve(index+1,nextS);
            ans.first+= ret.first;
            ans.second+=ret.second;
            if(i==1){
                ans.second+= ret.first;
            }
        }
        return dp[index][smaller] = ans;
    }
    int countDigitOne(int n) {
        while(n){
            nums.push_back(n%10);
            n/=10;
        }   
        reverse(nums.begin(),nums.end());
        for(int i= 0 ; i < 10 ; i ++)for(int j = 0 ;j < 2 ; j ++)dp[i][j] = {-1,-1};
        return solve(0).second;
        
    }
};
