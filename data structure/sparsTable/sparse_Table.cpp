struct sparseTable {
    vector<vector<int>> table;
 
    sparseTable();
 
    sparseTable(vector<int> vec) {
        int n = vec.size();
        table.resize(n, vector<int>(20));
        for (int i = 0; i < n; i++) {
            table[i][0] = vec[i];
        }
        for (int i = 1; i <= 20; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                table[j][i] = __gcd(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
 
    int query(int a, int b) {
        int s = log2(b - a + 1);
        return __gcd(table[a][s], table[b - (1 << s) + 1][s]);
    }
};
