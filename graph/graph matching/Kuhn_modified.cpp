struct graphMatching {
    // used to find a dual assigmnet between pairs , as the node can't be assigned to more than one relation 
    vector<vector<int>> g;
    int n;
    vector<int> mt;
    vector<bool> used;

    bool try_kuhn(int v) {
        if (used[v])
            return false;
        used[v] = true;
        for (int to: g[v]) {
            if (mt[to] == -1 || try_kuhn(mt[to])) {
                mt[to] = v;
                mt[v] = to;
                return true;
            }
        }
        return false;
    }

    vector<pair<int, int >> solve() {
        mt.assign(n, -1);
        for (int v = 0; v < n; ++v) {
            used.assign(n, false);
            if (mt[v] == -1)
                try_kuhn(v);
        }

        vector<pair<int, int >> ans;
        for (int i = 0; i < n; ++i)
            if (mt[i] != -1) {
                if (mt[i] > i) {
                    ans.push_back({mt[i], i + 1});
                }
            }
        return ans;
    }

    graphMatching(vector<vector<int>> g) {
        this->g = g;
        n = g.size();
    }

};
