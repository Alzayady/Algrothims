struct Manachar {
    string str;
    int n = 0;
    vector<int> p;
    string hashed;

    Manachar(string str) {
        this->str = str;
        n = str.size();
        getHashed();
        p.resize(hashed.size());
        Manachar_();
    }

    void getHashed() {
        hashed = "";
        for (int i = 0; i < n; i++) {
            hashed += "#";
            hashed += str[i];
        }
        hashed += "#";
    }

    void Manachar_() {
        int l = 0;
        int r = 0;
        int s_h = hashed.size();
        //cout<<hashed<<endl;
        for (int i = 0; i < s_h; i++) {
            int mirror = l + (r - i);
            if (r > i) {
                // not on the border
              //  cout<<mirror<<endl;
                p[i] = min(p[mirror], r - i);
            } else {
                p[i] = 0;
            }
            while (i + 1 + p[i] < s_h && i - p[i] - 1 >= 0 && hashed[1 + i + p[i]] == hashed[i - p[i] - 1]) {
                p[i]++;
            }
            if (i + p[i] > r) {
                r = p[i] + i;
                l =  i - p[i] ;

            }

        }
    }

    int get_length_max_palindrome() {
        int len = 0;
        for (int num : p) {
            len = max(num, len);
        }
        return len;
    }

    string get_string_max_palindrome() {
        int len = get_length_max_palindrome();
        for (int i = 0; i < hashed.size(); i++) {
            if (len == p[i]) {
                return str.substr((i - len)/2, len);
            }
        }
        assert(false);
    }

    int num_of_max_palindrome_string() {
        int len = get_length_max_palindrome();
        int ans = 0;
        for (int num : p) {
            if (len == num) {
                ans++;
            }
        }
        return ans;
    }


};
