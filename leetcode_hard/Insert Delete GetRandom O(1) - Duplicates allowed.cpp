mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());


struct fenwick{
    vector<int>tree;
    int n ;
    fenwick(int n){
        this->n =n +1;
        tree.resize(n+10);
        
    }
    void add(int index , int v){
        for(++index ; index < n ; index += index  & -index){
            tree[index]+=v;
        }
        
    }
    int sum(int index){
        int ans = 0;
        for( ++index ;index >0 ; index -= index & -index){
            ans+=tree[index];
        }
        return ans;
    }
};
class RandomizedCollection {
public:
    fenwick f =  fenwick(100010);
    int s = 0 ;
    int cur = 1 ;
    unordered_map<int , int > decode;
    unordered_map<int , int> encode;
    RandomizedCollection() {
    
    }
    
    bool insert(int val) {
        if(!decode.count(val)){
            decode[val] = cur;
            encode[cur] = val;
            cur++;
        }
        val =decode[val];
        s++;
        bool a = f.sum(val)==f.sum(val-1);
        f.add(val,1);
        return a;
    }
    
    bool remove(int val) {
        if(decode.count(val)==0)return 0 ;
        val = decode[val];
        if(f.sum(val)==f.sum(val-1))return 0;
        s--;
        f.add(val,-1);
        return 1 ;
    }
    
    int getRandom() {
        int k =  rng() % s + 1  ;
        int l = 1;
        int r = 10000;
        int ans = -1;
        while(l<=r){
            int mid = (l+r)/2;
            int sum = f.sum(mid);
            if(f.sum(mid) >= k and f.sum(mid-1)< k) ans = mid;
            if(sum >= k ){
                r = mid - 1 ;
            }else{
                l = mid + 1  ; 
            }
        }
        return encode[ans];
        
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
// using namespace __gnu_pbds;

