struct SegmentTreeLazyPropagation {
    vector<int> tree;
    vector<int> lazy;
    vector<int> pre;

    void propagate(int node) {
        if (lazy[node]) {
            lazy[node * 2] += lazy[node];
            tree[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
            tree[node * 2 + 1] += lazy[node];
            lazy[node] = 0; 
        }
    }

    SegmentTreeLazyPropagation(int n, vector<int> pre) {
        tree.resize(n * 6);
        lazy.resize(n * 6);
        this->pre = pre;
        build(1, 0, n - 1);
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = pre[l];
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    int getMax(int node, int l, int r, int ql, int qr) {
        propagate(node);
        if (l >= ql and r <= qr) {
            return tree[node];
        }
        if (r < ql or l > qr)return -1e18;
        int mid = (l + r) / 2;
        int left = getMax(node * 2, l, mid, ql, qr);
        int right = getMax(node * 2 + 1, mid + 1, r, ql, qr);
        return max(left, right);
    }

    void insert(int node, int l, int r, int ql, int qr, int v) {
        propagate(node);
        if (l >= ql and r <= qr) {
            tree[node] += v;  
            lazy[node] += v;
            // note :: tree node must be updated here not in propagate function as it will be used after returnd from recursion then it must use the newest value
            return;
        }
        if (r < ql or l > qr)return;
        int mid = (l + r) / 2;
        insert(node * 2, l, mid, ql, qr, v);
        insert(node * 2 + 1, mid + 1, r, ql, qr, v);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
};
