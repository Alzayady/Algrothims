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
        vector<int>sev(1e5+10,-1);
        for(int i = 2 ; i <= 1e5 ; i++){
            if(sev[i]==-1){
                sev[i] = i ;
                for(long long j = 1ll* i * i ; j<= 1e5 ; j+=i){
                    sev[j] = i ;
                }
            }
        }
        map<int , int > m ;
        int cur = -1 ;
        for(int i : nums){
            cur ++;
            while(i > 1){
                int f = sev[i];
                i/=f;
                if(m.count(f)){
                    make_parent(cur,m[f]);
                }else{
                    m[f] = cur ;
                }
            }
        }
        int ans = 0 ;
        map<int , int > rep ;
        for(int i = 0; i  < n ; i ++){
            rep[get_parent(i)]++;
        }
        for(auto it : rep){
            ans = max(ans , it.second);
        }
        return ans;
        
    }
};
