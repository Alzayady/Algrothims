class Solution {
public:
  
    const int INF = 1000000;
    int maxEnvelopes(vector<vector<int>>& vec) {
        int n = vec.size();
        sort(vec.begin(),vec.end(),[&](vector<int> a , vector<int> b){
           if(a[0] == b[0]){
               return a[1] > b[1];
           } 
            return a[0] < b[0];
        });
        vector<int> w (n);
        for(int i = 0 ; i < n ; i ++ ){
            w[i] = vec[i][1];
        }
        return LIS(w);
    }
    int LIS(vector<int> vec){
        int n = vec.size();
        vector<int> lis(n , INF);
        int ans = 0; 
        for(int i = 0 ; i< n ; i ++){
            int l = 0; 
            int r = n - 1 ; 
            int pos = -1;
            while(l<=r){ 
                int mid = (l + r) /2;
                if(lis[mid] >= vec[i]){ // 0 5 8 10 INF INF INF 
                    pos = mid ;
                    r  = mid - 1 ;
                }else{
                    l = mid + 1 ;
                }
            }            
            ans = max(ans , pos + 1 );
            lis[pos] = min(lis[pos] , vec[i]);
        }
        return ans;
    }
};
