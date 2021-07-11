class MedianFinder {
public:
    
    /** initialize your data structure here. */
    const int N = 2e5 +10;
    const int shift = 1e5;
    struct fenwick{
        vector<int> tree;
        int n ;
        fenwick(int n ){
            this->n = n + 1;
            tree.resize(this->n);
        }
        void append(int index ){
            for(++index ; index< n ; index+=index & - index){
                tree[index]++;
            }
        }
        int get(int index){
            int ans = 0; 
            for(++index ; index >0  ; index -= index & - index){
                ans+=tree[index];
            }
            return ans;
        }
    };
    fenwick *f ;
    int n = 0 ;
    MedianFinder() {
        f = new fenwick(N);
    }
    
    void addNum(int num) {
        num+=shift;
        f->append(num);
        n++;
    }
    int solve(int index){
        int l = 0 ;
        int r = 2e5;
        int ans = -1;
        while(l<=r){
            int mid = (l+r)/2;
            int last = f->get(mid);
            if(last>=index){
                ans = mid ;
                r = mid - 1 ;
            }else{
                l = mid + 1 ;
            }
        }
        return ans - shift;
    }
    double solve_even(){
        int a = solve(n/2);
        int b = solve(n/2+1);
        return (1.0*a + b ) / 2;
    }
    double solve_odd(){
        return solve(n/2+1);
    }
    
    double findMedian() {
        if(n%2 == 0 ){
            return solve_even();
        }else{
            return solve_odd();
        }
    }
};
