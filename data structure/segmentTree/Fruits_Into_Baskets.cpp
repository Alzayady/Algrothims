struct seg {
    vector<int> vec;
    vector<int> tree;
    int n ;
    seg(vector<int> vec){
        this->vec= vec;
        this-> n = vec.size();
        tree.resize(n*4);
        build(1,0,n-1);
    }

    void build(int node , int l , int r){
        if(l == r){
            tree[node] = vec[l];
            return;
        }
        int mid = (l+r) / 2;
        build(node * 2, l , mid);
        build(node * 2 + 1, mid + 1 , r);
        tree[node] = max(tree[node * 2] , tree[node * 2 + 1]);
    }

    bool take(int value){
        return take(1 , 0 , n - 1, value);
    }

    bool take(int node , int l , int r , int value)
    {
        if(l == r){
            if(tree[node] >= value){
                // take
                tree[node] = 0;
                return true;
            }
            return false;
            // assert(false);
        }
        int mid = (l+r) / 2;
        if(tree[node * 2] >= value){
            // can go lift
            take(node * 2 , l , mid, value);
        }else if(tree[node * 2 + 1] >= value){
            // can go right
            take(node * 2 + 1 , mid + 1 , r, value);
        }else {
            return false;
        }
        tree[node] = max(tree[node * 2] , tree[node * 2 + 1]);
        return true;
    }

};

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        seg * s = new seg(baskets);
        int ans = 0 ;
        for(auto it : fruits){
            ans += !s->take(it);
        }
        return ans;
    }
};
