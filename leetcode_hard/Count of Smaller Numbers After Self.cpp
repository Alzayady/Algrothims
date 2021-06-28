class Solution {
public:
    struct fenwick{
        vector<int>tree;
        int n ;
        fenwick(int n){
            this->n = n +1 ;
            tree.resize(n+1);
        }
        void add(int index){
            for(++index ; index < n ; index += index & - index){
                tree[index]++;
            }
        }
        int sum(int index){
            int ans = 0 ;
            for(++index ; index >0 ; index -= index & - index){
                ans+=tree[index];
            }
            return ans;
        }
    };
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        fenwick * f = new fenwick(2*1e4+100);
        for(int i =  n - 1 ; i >= 0 ; i --){
            int k = nums[i];
            nums[i] = f->sum(k-1 + 1e4 + 10 );
            f->add(k + 1e4 + 10);
        }
        return nums;
        
    }
};
