void Rabin-Karp(string str){
    const int SEED = 117;
    int n = str.size();
    for (int i = 1; i <= n; i++) {
        unordered_set<unsigned long long> hashed;
        unsigned long long EXP = 1, hash = 0;
        for (int j = 0; j < i; j++) {
            EXP *= SEED;
            hash = hash * SEED + str[j] - 'a' + 1;
        }
        for (int j = 1; j < n - i + 1; j++) {
            hash = hash * SEED - (str[j - 1] - 'a' + 1)  * EXP + str[i + j - 1] - 'a' + 1;
            // hasing of each substring of lenght i 
        }
    }
}
