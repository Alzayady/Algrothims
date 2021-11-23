class Solution {
public:
    vector<int>dsu;
    void make_parent(int a , int b){
        a = get_parent(a);
        b = get_parent(b);
        dsu[a] = b;
    }
    int get_parent(int a){
        if(dsu[a] == a){
            return a;
        }
        return dsu[a] =  get_parent(dsu[a]);
    }
    
    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        dsu.resize(n+2);
        for(int i = 0; i < n ; i ++){
            dsu[i] = i ;
        }
        int mm = 0;
        for(int i : nums)mm=max(mm,i);
        vector<int>sev(mm+1,-1);
        for(int i = 2 ; i <= mm ; i++){
            if(sev[i]==-1){
                sev[i] = i ;
                for(long long j = 1ll* i * i ; j<= mm ; j+=i){
                    sev[j] = i ;
                }
            }
        }
        vector<int>m(mm+1,-1);
        int cur = -1 ;
        for(int i : nums){
            cur ++;
            while(i > 1){
                int f = sev[i];
                i/=f;
                if(m[f]!=-1){
                    make_parent(cur,m[f]);
                }else{
                    m[f] = cur ;
                }
            }
        }
        int ans = 0 ;
        vector<int> rep(mm+1) ;
        for(int i = 0; i  < n ; i ++){
            int p =get_parent(i);
            rep[p]++;
            ans = max(ans,rep[p]);
        }
        return ans;
        
    }
};
