#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
#include <time.h>
#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long int ll;
int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    IO;
    int n ;
    cin>>n ;
    int best_a=0,best_b=0,best_c=0;
    int a , b ,c ;
    for(int i =0 ;i < n ; i++){
        cin>>a>>b>>c;
        int t_a=best_a,t_b=best_b,t_c=best_c;
        best_a=max(t_b,t_c)+a;
        best_b=max(t_a,t_c)+b;
        best_c=max(t_a,t_b)+c;
    }
    cout<<max({best_a,best_b,best_c})<<endl;

    return 0;
}
